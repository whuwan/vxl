// This is core/vil/tests/test_stream.cxx
#include <testlib/testlib_test.h>
#include <testlib/testlib_root_dir.h>

#include <vcl_string.h>

#include <vil/vil_stream_fstream.h>
#include <vxl_config.h>

#if defined(VCL_WIN32) && VXL_USE_WIN_WCHAR_T
# include <windows.h>
#endif

static void
test_stream( int argc, char* argv[] )
{
  // path not passed in to argv by CMake
#if 0
  if ( argc < 2 ) {
    vcl_cerr << "Supply file_read_data directory as the first argument\n";
    TEST("vil_stream", true, false);
    return;
  }
#endif
  //vcl_string dir = argv[1];
#ifndef VIL_IMG_PATH
  TEST("Path not defined", true, true);
 return;
#endif
  vcl_string dir = TEST_PATH_DEFINE(VIL_IMG_PATH);
  {
    vil_stream* fs = new vil_stream_fstream( (dir+"/ff_grey8bit_compressed.jpg").c_str(), "r" );
    fs->ref();
    TEST( "Open file 1", fs->ok(), true );
    TEST( "Size file 1", fs->file_size(), 421 );
    fs->unref();
  }

  {
    vil_stream* fs = new vil_stream_fstream( (dir+"/ff_rgb8bit_littleendian.viff").c_str(), "r" );
    fs->ref();
    TEST( "Open file 2", fs->ok(), true );
    TEST( "Size file 2", fs->file_size(), 1069 );
    fs->unref();
  }

#if defined(VCL_WIN32) && VXL_USE_WIN_WCHAR_T
  const unsigned int size = 4096;  // should be enough
  std::wstring wdir;
  wdir.resize(size);
  const int ret = MultiByteToWideChar(CP_ACP, 0, dir.c_str(), int(dir.size()), &wdir[0], size);
  TEST( "dir name converts to wchart_t type", ret>0, true );
  wdir.resize(ret);

  {
    vil_stream* fs = new vil_stream_fstream( (wdir+L"/ff_grey8bit_compressed.jpg").c_str(), "r" );
    fs->ref();
    TEST( "[wchar_t] Open file 1", fs->ok(), true );
    TEST( "[wchar_t] Size file 1", fs->file_size(), 421 );
    fs->unref();
  }

  {
    vil_stream* fs = new vil_stream_fstream( (wdir+L"/ff_rgb8bit_littleendian.viff").c_str(), "r" );
    fs->ref();
    TEST( "[wchar_t] Open file 2", fs->ok(), true );
    TEST( "[wchar_t] Size file 2", fs->file_size(), 1069 );
    fs->unref();
  }
#endif //defined(VCL_WIN32) && VXL_USE_WIN_WCHAR_T
}

TESTMAIN_ARGS(test_stream);
