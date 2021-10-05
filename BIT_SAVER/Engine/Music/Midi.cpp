#include "Midi.h"
#include <fstream>
#include "..\Engine.h"

int m_ticksPerQuarterNote = 120;

std::map<int, std::vector<long double>> MidiEvent::MidiSetUp(std::string filename)
{
    //open midi file

    std::ifstream input{ filename, std::ios::in };


	if (!input)
	{
		exit(EXIT_FAILURE);
	}


    //check Mthd
    int    character;
    character = input.get();//'M'
    character = input.get();//'T'
    character = input.get();//'h'
    character = input.get();//'d'


    unsigned long  longdata;
    unsigned char buffer[4] = { 0 };
    input.read((char*)buffer, 4);
    if (input.eof()) {
	Engine::GetLogger().LogError("Error: unexpected end of file.");
	exit(EXIT_FAILURE);
    }
    longdata = buffer[3] | (buffer[2] << 8) | (buffer[1] << 16) | (buffer[0] << 24);
    //if (longdata != 6) {
    //    std::cerr << "File " << filename
    //        << " is not a MIDI 1.0 Standard MIDI file." << std::endl;
    //    std::cerr << "The header size is " << longdata << " bytes." << std::endl;
    //    m_rwstatus = false; return m_rwstatus;
    //}
    // 
    // 
    //check format
    int type=0;
    unsigned short  shortdata;
    buffer[2] = { 0 };
    input.read((char*)buffer, 2);
    shortdata = buffer[1] | (buffer[0] << 8);

    switch (shortdata) {
    case 0:
	type = 0;
	break;
    case 1:
	type = 1;
	break;
    case 2:
	// Type-2 MIDI files should probably be allowed as well,
	// but I have never seen one in the wild to test with.
    default:
	std::cerr << "Error: cannot handle a type-" << shortdata
	    << " MIDI file" << std::endl;
    }

    //check track count
    int tracks=0;
    buffer[2] = { 0 };
    input.read((char*)buffer, 2);
    shortdata = buffer[1] | (buffer[0] << 8);

    if (type == 0 && shortdata != 1) {
	std::cerr << "Error: Type 0 MIDI file can only contain one track" << std::endl;
	std::cerr << "Instead track count is: " << shortdata << std::endl;
    }
    else {
	tracks = shortdata;
    }

    // TODO:  allocate storage for each tracks

    // Ticks per quarter note 
    buffer[2] = { 0 };
    input.read((char*)buffer, 2);
    shortdata = buffer[1] | (buffer[0] << 8);
    if (shortdata >= 0x8000) {
	int framespersecond = 255 - ((shortdata >> 8) & 0x00ff) + 1;
	int subframes = shortdata & 0x00ff;
	switch (framespersecond) {
	case 25:  framespersecond = 25; break;
	case 24:  framespersecond = 24; break;
	case 29:  framespersecond = 29; break;  // really 29.97 for color television
	case 30:  framespersecond = 30; break;
	default:
	    std::cerr << "Warning: unknown FPS: " << framespersecond << std::endl;
	    std::cerr << "Using non-standard FPS: " << framespersecond << std::endl;
	}
	m_ticksPerQuarterNote = framespersecond * subframes;

	// std::cerr << "SMPTE ticks: " << m_ticksPerQuarterNote << " ticks/sec" << std::endl;
	// std::cerr << "SMPTE frames per second: " << framespersecond << std::endl;
	// std::cerr << "SMPTE subframes per frame: " << subframes << std::endl;
    }
    else {
	m_ticksPerQuarterNote = shortdata;
    }

    unsigned char runningCommand;
    MidiEvent event;
    std::vector<unsigned char> bytes;
    unsigned long tempo_data = 0;
    long double one_tick_per_tempo = 0;
    for (int i = 0; i < tracks; i++) {
	runningCommand = 0;

	character = input.get();
	character = input.get();
	character = input.get();
	character = input.get();

	input.read((char*)buffer, 4);
	if (input.eof()) {
	    Engine::GetLogger().LogError("Error: unexpected end of file.");
	    exit(EXIT_FAILURE);
	}
	longdata = buffer[3] | (buffer[2] << 8) | (buffer[1] << 16) | (buffer[0] << 24);

	// Read MIDI events in the track, which are pairs of VLV values
	// and then the bytes for the MIDI message.  Running status messags
	// will be filled in with their implicit command byte.
	// The timestamps are converted from delta ticks to absolute ticks,
	// with the absticks variable accumulating the VLV tick values.
	int absticks = 0;

	while (!input.eof()) {

	    longdata = event.readVLValue(input);
	    absticks += longdata;
	    event.extractMidiData(input, bytes, runningCommand);
	    if (bytes[0] == 0xff && bytes[1] == 0x51)
	    {
		for (int j = 0; j < bytes[2]; j++)
		{
		    tempo_data = tempo_data | (bytes[bytes.size() - 1 - j] << 8 * j);
		}
	    }

	    //event.setMessage(bytes);
	    event.tick = absticks;
	    event.track = i;

	    if (bytes[0] == 0xff && bytes[1] == 0x2f) {
		// end-of-track message
		// comment out the following line if you don't want to see the
		// end of track message (which is always required, and will added
		// automatically when a MIDI is written, so it is not necessary.
		m_events.push_back(event);
		break;
	    }
	    m_events.push_back(event);
	}
	//m_theTimeState = TIME_STATE_ABSOLUTE;
	//markSequence();

    }
    one_tick_per_tempo = (tempo_data * 0.000001) / m_ticksPerQuarterNote;
    std::map<int, std::vector<long double>> H;


    for (int i = 1; i < tracks; i++)

    {
	std::vector<long double> A;
	for (auto& m : m_events)
	{
	    if (m.track == i)
	    {
		if (m.tick != 0)
		{
		    A.push_back(m.tick * one_tick_per_tempo);
		}
	    }
	}
	H.emplace(i, A);
    }

    input.close();

    return H;
}

unsigned char MidiEvent::readByte(std::istream& input) {
    unsigned char buffer[1] = { 0 };
    input.read((char*)buffer, 1);
    if (input.eof()) {
	std::cerr << "Error: unexpected end of file." << std::endl;
	return 0;
    }
    return buffer[0];
}

unsigned long MidiEvent::unpackVLV(unsigned char a, unsigned char b, unsigned char c, unsigned char d, unsigned char e) {
    unsigned char bytes[5] = { a, b, c, d, e };
    int count = 0;
    while ((count < 5) && (bytes[count] > 0x7f)) {
	count++;
    }
    count++;
    if (count >= 6) {
	std::cerr << "VLV number is too large" << std::endl;
	return 0;
    }

    unsigned long output = 0;
    for (int i = 0; i < count; i++) {
	output = output << 7;
	output = output | (bytes[i] & 0x7f);
    }

    return output;
}

unsigned long MidiEvent::readVLValue(std::istream& input) {
    unsigned char b[5] = { 0 };

    for (int i = 0; i < 5; i++) {
	b[i] = readByte(input);
	if (b[i] < 0x80) {
	    break;
	}
    }

    return unpackVLV(b[0], b[1], b[2], b[3], b[4]);
}

int MidiEvent::extractMidiData(std::istream& input, std::vector<unsigned char>& array,
    unsigned char& runningCommand) {

    int character;
    unsigned char byte;
    array.clear();
    int runningQ;

    character = input.get();
    if (character == EOF) {
	std::cerr << "Error: unexpected end of file." << std::endl;
	return 0;
    }
    else {
	byte = (unsigned char)character;
    }

    if (byte < 0x80) {
	runningQ = 1;
	if (runningCommand == 0) {
	    std::cerr << "Error: running command with no previous command" << std::endl;
	    return 0;
	}
	if (runningCommand >= 0xf0) {
	    std::cerr << "Error: running status not permitted with meta and sysex"
		<< " event." << std::endl;
	    std::cerr << "Byte is 0x" << std::hex << (int)byte << std::dec << std::endl;
	    return 0;
	}
    }
    else {
	runningCommand = byte;
	runningQ = 0;
    }

    array.push_back(runningCommand);
    if (runningQ) {
	array.push_back(byte);
    }

    switch (runningCommand & 0xf0) {
    case 0x80:        // note off (2 more bytes)
    case 0x90:        // note on (2 more bytes)

    case 0xA0:        // aftertouch (2 more bytes)
    case 0xB0:        // cont. controller (2 more bytes)
    case 0xE0:        // pitch wheel (2 more bytes)

	byte = readByte(input);

	if (byte > 0x7f) {
	    std::cerr << "MIDI data byte too large: " << (int)byte << std::endl;
	}
	array.push_back(byte);
	if (!runningQ) {
	    byte = readByte(input);

	    if (byte > 0x7f) {
		std::cerr << "MIDI data byte too large: " << (int)byte << std::endl;

	    }
	    array.push_back(byte);
	}
	break;
    case 0xC0:        // patch change (1 more byte)
    case 0xD0:        // channel pressure (1 more byte)
	if (!runningQ) {
	    byte = readByte(input);

	    if (byte > 0x7f) {
		std::cerr << "MIDI data byte too large: " << (int)byte << std::endl;

	    }
	    array.push_back(byte);
	}
	break;
    case 0xF0:
	switch (runningCommand) {
	case 0xff:                 // meta event
	{
	    if (!runningQ) {
		byte = readByte(input); // meta type

		array.push_back(byte);
	    }
	    unsigned long length = 0;
	    unsigned char byte1 = 0;
	    unsigned char byte2 = 0;
	    unsigned char byte3 = 0;
	    unsigned char byte4 = 0;
	    byte1 = readByte(input);

	    array.push_back(byte1);
	    if (byte1 >= 0x80) {
		byte2 = readByte(input);

		array.push_back(byte2);
		if (byte2 > 0x80) {
		    byte3 = readByte(input);

		    array.push_back(byte3);
		    if (byte3 >= 0x80) {
			byte4 = readByte(input);

			array.push_back(byte4);
			if (byte4 >= 0x80) {
			    std::cerr << "Error: cannot handle large VLVs" << std::endl;
			    //m_rwstatus = false; return m_rwstatus;
			}
			else {
			    length = unpackVLV(byte1, byte2, byte3, byte4);
			    // if (!m_rwstatus) { return m_rwstatus; }
			}
		    }
		    else {
			length = unpackVLV(byte1, byte2, byte3);
			//if (!m_rwstatus) { return m_rwstatus; }
		    }
		}
		else {
		    length = unpackVLV(byte1, byte2);
		    //if (!m_rwstatus) { return m_rwstatus; }
		}
	    }
	    else {
		length = byte1;
	    }
	    for (int j = 0; j < (int)length; j++) {
		byte = readByte(input); // meta type

		array.push_back(byte);
	    }
	}
	break;

	// The 0xf0 and 0xf7 meta commands deal with system-exclusive
	// messages. 0xf0 is used to either start a message or to store
	// a complete message.  The 0xf0 is part of the outgoing MIDI
	// bytes.  The 0xf7 message is used to send arbitrary bytes,
	// typically the middle or ends of system exclusive messages.  The
	// 0xf7 byte at the start of the message is not part of the
	// outgoing raw MIDI bytes, but is kept in the MidiFile message
	// to indicate a raw MIDI byte message (typically a partial
	// system exclusive message).
	case 0xf7:   // Raw bytes. 0xf7 is not part of the raw
		     // bytes, but are included to indicate
		     // that this is a raw byte message.
	case 0xf0:   // System Exclusive message
	{         // (complete, or start of message).
	    int length = (int)readVLValue(input);
	    for (int i = 0; i < length; i++) {
		byte = readByte(input);

		array.push_back(byte);
	    }
	}
	break;

	// other "F" MIDI commands are not expected, but can be
	// handled here if they exist.
	}
	break;
    default:
	std::cout << "Error reading midifile" << std::endl;
	std::cout << "Command byte was " << (int)runningCommand << std::endl;
	return 0;
    }
    return 1;
}