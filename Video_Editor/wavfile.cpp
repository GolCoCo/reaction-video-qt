#include "wavfile.h"

WavManager::WavManager(string filepath, string binaryFile)
{
		_wavheader2 = new char[33];
		_headerSize = sizeof(wav_hdr);
		_filelength = 0;
		isempty = false;
		inputfilepath = filepath;
		_binaryFile = binaryFile;

}
int WavManager::openRecWavFile() {

	int i = fopen_s(&_inputWav, inputfilepath.c_str(), "rb");
	fread(&_wavheader, sizeof(wav_hdr), 1, _inputWav);
	fread(&_wavheader2, 33, 1, _inputWav);
	fopen_s(&rawWav, _binaryFile.c_str(), "wb");
	totalOutputChunkSize = 0;
	return 0;
}

WavManager::~WavManager()
{

}
void WavManager::readWavData(int start_time, double interval) {

	fclose(_inputWav);
	fopen_s(&_inputWav, inputfilepath.c_str(), "rb");

	double sec = interval / 1000;
	double offset_sec = start_time / 1000;
	int seekSize = (int)(offset_sec * _wavheader.bytesPerSec);
	int readBufSize = (int)(_wavheader.bytesPerSec * sec);
	_wavDataBuffer = new int16_t[readBufSize];

	for (int i = 0; i < readBufSize; i++) {
		_wavDataBuffer[i] = 0x0;
	}
	if (!isempty) {

		int seekok = fseek(_inputWav, _headerSize + 33 + seekSize, 1);
		fread(_wavDataBuffer, readBufSize, 1, _inputWav);
	}

	fwrite(_wavDataBuffer, readBufSize, 1, rawWav);

	totalOutputChunkSize = totalOutputChunkSize + readBufSize;
}
void WavManager::setEmptyWavData(bool isnoempty) {
	isempty = isnoempty;
}
void WavManager::CreateOutputWavFile(string filepath) {
	fclose(rawWav);
	string rawfilepath = "D:\\rawSoundFile.bin";
	fopen_s(&_outputWav, filepath.c_str(), "wb");
	fopen_s(&rawWav, rawfilepath.c_str(), "rb");

	wav_hdr outWavheader = _wavheader;
	outWavheader.ChunkSize = totalOutputChunkSize;
	fwrite(&outWavheader, sizeof(outWavheader), 1, _outputWav);
	fwrite(&_wavheader2, 33, 1, _outputWav);

	int16_t d;
	while (!feof(rawWav))
	{
		fread(&d, sizeof(d), 1, rawWav);
		fwrite(&d, sizeof(d), 1, _outputWav);
	}
	fclose(rawWav);
	fclose(_inputWav);
	fclose(_outputWav);
}
