#include <vcl_iostream.h>
#include <vcl_fstream.h>
#include <vcl_utility.h>

#include <vgl/vgl_test.h>
#include <vgl/io/vgl_io_line_segment_2d.h>


void test_line_segment_2d_double_io()
{
  vcl_cout << "***********************" << vcl_endl;
  vcl_cout << "Testing vgl_line_segment_2d<double> io" << vcl_endl;
  vcl_cout << "***********************" << vcl_endl;

  vgl_point_2d<double> end0(1.2,3.4);
  vgl_point_2d<double> end1(5.6,7.8);
  vgl_line_segment_2d<double> p_out(end0,end1), p_in;


  vsl_b_ofstream bfs_out("vgl_line_segment_2d_test_double_io.bvl.tmp");
  TEST ("Created vgl_line_segment_2d_test_double_io.bvl.tmp for writing",
         (!bfs_out), false);
  vsl_b_write(bfs_out, p_out);
  bfs_out.close();

  vsl_b_ifstream bfs_in("vgl_line_segment_2d_test_double_io.bvl.tmp");
  TEST ("Opened vgl_line_segment_2d_test_double_io.bvl.tmp for reading",
        (!bfs_in), false);
  vsl_b_read(bfs_in, p_in);
  bfs_in.close();



  TEST ("p_out == p_in", p_out.get_point1() == p_in.get_point1()
         && p_out.get_point2() == p_in.get_point2(), true);


    vsl_print_summary(vcl_cout, p_out);
  vcl_cout << vcl_endl;

}


void test_line_segment_2d_prime()
{
  test_line_segment_2d_double_io();
}


TESTMAIN(test_line_segment_2d_prime);
