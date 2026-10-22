#pragma once

// This is an ABI-compatible stand-in for the MSS32 API.

extern "C"
{
	struct _DIG_DRIVER;
	struct _SAMPLE;
	struct _STREAM;
	typedef _DIG_DRIVER* HDIGDRIVER;
	typedef _SAMPLE* HSAMPLE;
	typedef _STREAM* HSTREAM;

	struct AILSOUNDINFO
	{
		int format;
		const void* data;
		unsigned int data_len, rate;
		int bits, channels;
		unsigned int samples, block_size;
		const void* initial_ptr;
		int original_format;
	};

	__declspec(dllimport) void __stdcall AIL_set_digital_master_reverb(
		HDIGDRIVER, float, float, float);
	__declspec(dllimport) void __stdcall AIL_close_stream(HSTREAM);
	__declspec(dllimport) void __stdcall AIL_stop_sample(HSAMPLE);
	__declspec(dllimport) void __stdcall AIL_release_sample_handle(HSAMPLE);
	__declspec(dllimport) int __stdcall AIL_digital_CPU_percent(HDIGDRIVER);
	__declspec(dllimport) const void* __stdcall AIL_speaker_configuration(
		HDIGDRIVER, int*, int*, int*, int*);
	__declspec(dllimport) void __stdcall AIL_set_speaker_configuration(
		HDIGDRIVER, const void*, int, float);
	__declspec(dllimport) void __stdcall AIL_set_stream_loop_count(HSTREAM,
		int);
	__declspec(dllimport) HSAMPLE __stdcall AIL_stream_sample_handle(HSTREAM);
	__declspec(dllimport) void __stdcall AIL_set_sample_volume_pan(HSAMPLE,
		float, float);
	__declspec(dllimport) void __stdcall AIL_set_stream_position(HSTREAM, int);
	__declspec(dllimport) void __stdcall AIL_start_stream(HSTREAM);
	__declspec(dllimport) void __stdcall AIL_pause_stream(HSTREAM, int);
	__declspec(dllimport) int __stdcall AIL_stream_position(HSTREAM);
	__declspec(dllimport) void __stdcall AIL_set_sample_playback_rate(HSAMPLE,
		int);
	__declspec(dllimport) int __stdcall AIL_sample_playback_rate(HSAMPLE);
	__declspec(dllimport) void __stdcall AIL_set_sample_3D_distances(HSAMPLE,
		float, float, int);
	__declspec(dllimport) void __stdcall AIL_set_sample_3D_position(HSAMPLE,
		float, float, float);
	__declspec(dllimport) unsigned int __stdcall AIL_stream_status(HSTREAM);
	__declspec(dllimport) unsigned int __stdcall AIL_sample_status(HSAMPLE);
	__declspec(dllimport) unsigned int __stdcall AIL_sample_position(HSAMPLE);
	__declspec(dllimport) void __stdcall AIL_stream_ms_position(HSTREAM, int*,
		int*);
	__declspec(dllimport) void __stdcall AIL_stream_info(HSTREAM, int*, int*,
		int*, int*);
	__declspec(dllimport) int __stdcall AIL_file_size(const char*);
	__declspec(dllimport) void* __stdcall AIL_file_read(const char*, void*);
	__declspec(dllimport) int __stdcall AIL_file_type(const void*,
		unsigned int);
	__declspec(dllimport) int __stdcall AIL_decompress_ASI(const void*,
		unsigned int, const char*, void**, unsigned int*, void*);
	__declspec(dllimport) int __stdcall AIL_WAV_info(const void*,
		AILSOUNDINFO*);
	__declspec(dllimport) int __stdcall AIL_decompress_ADPCM(
		const AILSOUNDINFO*, void**, unsigned int*);
	__declspec(dllimport) void __stdcall AIL_mem_free_lock(void*);
	__declspec(dllimport) HSAMPLE __stdcall AIL_allocate_sample_handle(
		HDIGDRIVER);
	__declspec(dllimport) void __stdcall AIL_init_sample(HSAMPLE, int);
	__declspec(dllimport) HDIGDRIVER __stdcall AIL_open_digital_driver(
		unsigned int, int, int, unsigned int);
	__declspec(dllimport) const char* __stdcall AIL_last_error();
	__declspec(dllimport) void __stdcall AIL_set_DirectSound_HWND(HDIGDRIVER,
		HWND);
	__declspec(dllimport) int __stdcall AIL_set_named_sample_file(HSAMPLE,
		const char*, const void*, unsigned int, int);
	__declspec(dllimport) void __stdcall AIL_start_sample(HSAMPLE);
	__declspec(dllimport) void __stdcall AIL_set_sample_loop_count(HSAMPLE,
		int);
	__declspec(dllimport) int __stdcall AIL_set_sample_file(HSAMPLE,
		const void*, int);
	__declspec(dllimport) int __stdcall AIL_startup();
	__declspec(dllimport) void __stdcall AIL_set_file_callbacks(
		unsigned int(__stdcall*)(const char*, unsigned int*),
		void(__stdcall*)(unsigned int),
		int(__stdcall*)(unsigned int, int, unsigned int),
		unsigned int(__stdcall*)(unsigned int, void*, unsigned int));
	__declspec(dllimport) const char* __stdcall AIL_set_redist_directory(
		const char*);
	__declspec(dllimport) HSTREAM __stdcall AIL_open_stream(HDIGDRIVER,
		const char*, int);
	__declspec(dllimport) void __stdcall AIL_set_stream_user_data(HSTREAM,
		unsigned int, int);
	__declspec(dllimport) void __stdcall AIL_digital_handle_release(HDIGDRIVER);
	__declspec(dllimport) void __stdcall AIL_close_digital_driver(HDIGDRIVER);
	__declspec(dllimport) void __stdcall AIL_shutdown();
}
