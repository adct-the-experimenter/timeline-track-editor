#include "audio-stream-container.h"

AudioStreamContainer::AudioStreamContainer()
{
	input_audio_data_ptr = nullptr;
}

void AudioStreamContainer::SetReferenceToInputAudioData(std::vector <double> *input_audio_data){input_audio_data_ptr = input_audio_data;}


void AudioStreamContainer::ResizeAudioStream(size_t thisSize){stream_audio_data.resize(thisSize);}
size_t AudioStreamContainer::GetSize(){return stream_audio_data.size();}

void AudioStreamContainer::SetPointerToDataAtThisSampleIndex(double* thisRef,size_t i)
{
	stream_audio_data.at(i) = thisRef;
}

double* AudioStreamContainer::GetPointerToDataAtThisSampleIndex(size_t i)
{
	return stream_audio_data.at(i);
}

void AudioStreamContainer::CopyInputAudioDataToStream()
{
	if(input_audio_data_ptr != nullptr)
	{
		for(size_t i=0; i < input_audio_data_ptr->size(); i++)
		{
			double* thisRef = &(input_audio_data_ptr->at(i));
			stream_audio_data[i] = thisRef;
		}
	}
}

void AudioStreamContainer::WriteStreamContentsToFile()
{
	size_t read_size = 0;
	//while((read_size = sf_read_double(inputFile, audio_data_input_copy.data(), audio_data_input_copy.size())) != 0)
	//{
	//	sf_write_double (streamFile, audio_data_input_copy.data(), read_size) ;
	//}
}
