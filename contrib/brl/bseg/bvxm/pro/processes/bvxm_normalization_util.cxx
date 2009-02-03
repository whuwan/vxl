#include "bvxm_normalization_util.h"

#include <vcl_algorithm.h>
#include <vcl_cmath.h>

//: Float specialized function to normalize and image given a,b where new_I = a*I +b;
bool bvxm_normalization_util::normalize_image(const vil_image_view<float>& in_view,
    vil_image_view<float>& out_img,
    float a, float b, float max_value)
{
  unsigned ni = in_view.ni();
  unsigned nj = in_view.nj();
  unsigned np = in_view.nplanes();

  if (ni != out_img.ni() || nj != out_img.nj() || np != out_img.nplanes())
    return false;

  for (unsigned k=0;k<np;++k)
    for (unsigned j=0;j<nj;++j)
      for (unsigned i=0;i<ni;++i)
  {
    float p = a*in_view(i,j,k) + b;
        // Proposed fix
    out_img(i, j, k) = vcl_min(vcl_max(0.f, p), max_value);
  }

  return true;
}

//: Byte specialized function to normalize and image given a,b where new_I = a*I +b;
bool bvxm_normalization_util::normalize_image(const vil_image_view<vxl_byte>& in_view,
    vil_image_view<vxl_byte>& out_img,
    float a, float b, vxl_byte max_value)
{
  unsigned ni = in_view.ni();
  unsigned nj = in_view.nj();
  unsigned np = in_view.nplanes();

  if (ni != out_img.ni() || nj != out_img.nj() || np != out_img.nplanes())
    return false;

  for (unsigned k=0;k<np;++k)
    for (unsigned j=0;j<nj;++j)
      for (unsigned i=0;i<ni;++i)
  {
    int p = (int)vcl_floor(a*in_view(i,j,k) + b);
    out_img(i, j, k) = (vxl_byte)vcl_min(vcl_max(0, p), (int)max_value);
  }
#ifdef DEBUG
  vcl_cerr << "entered byte case..................\n";
#endif
  return true;
}
 