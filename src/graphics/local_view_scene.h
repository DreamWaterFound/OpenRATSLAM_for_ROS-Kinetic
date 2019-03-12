/*
 * openRatSLAM
 *
 * utils - General purpose utility helper functions mainly for angles and readings settings
 *
 * Copyright (C) 2012
 * David Ball (david.ball@qut.edu.au) (1), Scott Heath (scott.heath@uqconnect.edu.au) (2)
 *
 * RatSLAM algorithm by:
 * Michael Milford (1) and Gordon Wyeth (1) ([michael.milford, gordon.wyeth]@qut.edu.au)
 *
 * 1. Queensland University of Technology, Australia
 * 2. The University of Queensland, Australia
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef VIEW_TEMPLATE_SCENE_HPP_
#define VIEW_TEMPLATE_SCENE_HPP_

#include <irrlicht/irrlicht.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include "../utils/utils.h"
#include "../ratslam/local_view_match.h"

namespace ratslam
{

class LocalViewScene
{
public:
  LocalViewScene(ptree & settings, LocalViewMatch *in_vt)
  {

    get_setting_from_ptree(vt_window_width, settings, "vt_window_width", 640);
    get_setting_from_ptree(vt_window_height, settings, "vt_window_height", 480);

    update_ptr(in_vt);

    // the camera image is in the top half and the two template windows in the bottom half
    //  vt_window_height = vtm->IMAGE_HEIGHT * ((double)vt_window_width/vtm->IMAGE_WIDTH) * 2;

    /* ==============================↓↓↓↓↓==== [deleted] ====↓↓↓↓↓===================================
                      Following codes may disable the callback functions, so just delete them 

    device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(vt_window_width, vt_window_height), 32, false,
                               false, false);
    device->setWindowCaption(L"openRatSLAM Local View");

    driver = device->getVideoDriver();
    scene = device->getSceneManager();


    view_template_scene = scene->createNewSceneManager(false);
       ==============================↑↑↑↑↑==== [deleted] ====↑↑↑↑↑=================================== */
  
    // ===============================↓↓↓↓↓==== [added] ====↓↓↓↓↓====================================
    //                          We prefer to using OpenCV to display imgaes 
    //                One window is enought, if we can "montage" multiple imgaes together
    cv::namedWindow("openRatSLAM Local View");
    // ===============================↑↑↑↑↑==== [added] ====↑↑↑↑↑====================================

  }

  ~LocalViewScene()
  {
    // ===============================↓↓↓↓↓==== [added] ====↓↓↓↓↓====================================
    //                                 Remember to destroy windows 
    cv::destroyWindow("openRatSLAM Local View");
    // ===============================↑↑↑↑↑==== [added] ====↑↑↑↑↑====================================
  }

  void draw_all()
  {
    /* ==============================↓↓↓↓↓==== [deleted] ====↓↓↓↓↓===================================
    
    device->run(); // TODO return the bool for quiting
    driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
    // TODO not always true for greyscale
    draw_image(vtm->view_rgb, vtm->greyscale, -1.0f, 1.0f, vtm->IMAGE_WIDTH, vtm->IMAGE_HEIGHT, (double)vt_window_width/vtm->IMAGE_WIDTH, -(double)vt_window_width/vtm->IMAGE_WIDTH);

    draw_image((const double*)&vtm->templates[vtm->current_vt].data[0], true, -1, 0.0,
                               vtm->TEMPLATE_X_SIZE, vtm->TEMPLATE_Y_SIZE,
                               (double)vt_window_width/vtm->TEMPLATE_X_SIZE,
                               -(double)vt_window_height/vtm->TEMPLATE_Y_SIZE/4);

    draw_image((const double*)&vtm->current_view[0],true, -1.0, -0.5,
               vtm->TEMPLATE_X_SIZE, vtm->TEMPLATE_Y_SIZE,
               (double)vt_window_width/vtm->TEMPLATE_X_SIZE,
               -(double)vt_window_height/vtm->TEMPLATE_Y_SIZE/4);
    view_template_scene->drawAll();
    driver->endScene();
        ==============================↑↑↑↑↑==== [deleted] ====↑↑↑↑↑=================================== */
  
    // ===============================↓↓↓↓↓==== [added] ====↓↓↓↓↓====================================
    
    cv::Mat img1=convertImage(vtm->IMAGE_HEIGHT,vtm->IMAGE_WIDTH,false,vtm->view_rgb);  

    cv::Mat img2;
    cv::resize(
      convertImage(vtm->TEMPLATE_Y_SIZE,vtm->TEMPLATE_X_SIZE,true,(const double*)&vtm->templates[vtm->current_vt].data[0]),
      img2,
      cv::Size(vtm->IMAGE_WIDTH,vtm->TEMPLATE_Y_SIZE*(1.0f*(vtm->IMAGE_WIDTH)/vtm->TEMPLATE_X_SIZE)));

    cv::Mat img3;
    cv::resize(
      convertImage(vtm->TEMPLATE_Y_SIZE,vtm->TEMPLATE_X_SIZE,true,(const double*)&vtm->current_view[0]),
      img3,
      cv::Size(vtm->IMAGE_WIDTH,vtm->TEMPLATE_Y_SIZE*(1.0f*(vtm->IMAGE_WIDTH)/vtm->TEMPLATE_X_SIZE)));

    cv::Mat merge;
    merge.push_back(img1);
    merge.push_back(img2);
    merge.push_back(img3);
    
    cv::imshow("openRatSLAM Local View",merge);
    cv::waitKey(10);
    // ===============================↑↑↑↑↑==== [added] ====↑↑↑↑↑====================================


  }

  void update_ptr(LocalViewMatch *vt_in)
  {
    vtm = vt_in;
  }

private:

  /* ==============================↓↓↓↓↓==== [deleted] ====↓↓↓↓↓===================================
  void draw_image(const double * image, bool greyscale, float x, float y, int width, int height, double scale_x, double scale_y)
   {
    unsigned char* texture_ptr_start = (unsigned char *) malloc(width*height * (greyscale ? 1 : 3));

    const double * image_ptr = image;
    const double * image_end = image_ptr + width * height * (greyscale ? 1 : 3);
    unsigned char *texture_ptr = texture_ptr_start;
    for (; image_ptr < image_end;)
    {
      *(texture_ptr++) = (unsigned char)(*(image_ptr++) * 255.0);
    }

    draw_image(texture_ptr_start, greyscale, x, y, width, height, scale_x, scale_y);
    free(texture_ptr_start);
   }

   void draw_image(const unsigned char * image, bool greyscale, float x, float y, int width, int height, double scale_x, double scale_y)
   {
     glRasterPos2f(x,y);
     glPixelZoom(scale_x, scale_y);
     if (greyscale)
       glDrawPixels(width, height, GL_LUMINANCE, GL_UNSIGNED_BYTE, image);
     else
       glDrawPixels(width, height, GL_BGR, GL_UNSIGNED_BYTE, image);
   }
      ==============================↑↑↑↑↑==== [deleted] ====↑↑↑↑↑=================================== */
   
   // ===============================↓↓↓↓↓==== [added] ====↓↓↓↓↓====================================
   cv::Mat convertImage(size_t rows, size_t cols, bool isGray, const double* data)
   {
    cv::Mat res;

    if(isGray)
    {
      res=cv::Mat(rows,cols,CV_8UC3);

      //这里之所以还是作为彩色图像处理,主要是为了混合显示的方便
      for(int row=0;row<rows;row++)           //行的个数和 IMAGE_HEIGHT 相等
          for(int col=0;col<(cols);col++)     //列数和 IMAGE_WIDTH 相等
          {
            //res.at<unsigned char>(row,col)=(unsigned char)((data)[row*cols+col]*255.0);
            
            res.at<unsigned char>(row,3*col  )=(unsigned char)((data)[row*cols+col]*255.0);
            res.at<unsigned char>(row,3*col+1)=(unsigned char)((data)[row*cols+col]*255.0);
            res.at<unsigned char>(row,3*col+2)=(unsigned char)((data)[row*cols+col]*255.0);
            
          }
    }
    else
    {
      res=cv::Mat(rows,cols,CV_8UC3);
      for(int row=0;row<rows;row++)         //行的个数和 IMAGE_HEIGHT 相等
          for(int col=0;col<cols;col++)     //列数和 IMAGE_WIDTH 相等
          {
            res.at<unsigned char>(row,3*col  )=(unsigned char)((data)[3*(row*(cols)+col)  ]*255.0);
            res.at<unsigned char>(row,3*col+1)=(unsigned char)((data)[3*(row*(cols)+col)+1]*255.0);
            res.at<unsigned char>(row,3*col+2)=(unsigned char)((data)[3*(row*(cols)+col)+2]*255.0); 
          }
    }

    return res;
   }

  
   cv::Mat convertImage(size_t rows, size_t cols, bool isGray, const unsigned char* data)
   {
    cv::Mat res;

    if(isGray)
    {
      res=cv::Mat(rows,cols,CV_8UC3);

      //这里之所以还是作为彩色图像处理,主要是为了混合显示的方便
      for(int row=0;row<rows;row++)           //行的个数和 IMAGE_HEIGHT 相等
          for(int col=0;col<(cols);col++)     //列数和 IMAGE_WIDTH 相等
          {
            
            res.at<unsigned char>(row,3*col  )=(data)[(row*(cols)+col)];
            res.at<unsigned char>(row,3*col+1)=(data)[(row*(cols)+col)];
            res.at<unsigned char>(row,3*col+2)=(data)[(row*(cols)+col)]; 
            
          }
    }
    else
    {
      res=cv::Mat(rows,cols,CV_8UC3);
      for(int row=0;row<rows;row++)         //行的个数和 IMAGE_HEIGHT 相等
          for(int col=0;col<cols;col++)     //列数和 IMAGE_WIDTH 相等
          {
            res.at<unsigned char>(row,3*col  )=(data)[3*(row*(cols)+col)  ];
            res.at<unsigned char>(row,3*col+1)=(data)[3*(row*(cols)+col)+1];
            res.at<unsigned char>(row,3*col+2)=(data)[3*(row*(cols)+col)+2]; 
          }
    }

    return res;
   }
  // ===============================↑↑↑↑↑==== [added] ====↑↑↑↑↑====================================

  /* ==============================↓↓↓↓↓==== [deleted] ====↓↓↓↓↓===================================
                                        Useless variables

  irr::IrrlichtDevice *device;
  irr::video::IVideoDriver * driver;
  irr::scene::ISceneManager * scene;
  
  irr::scene::ISceneManager * view_template_scene;
  ==============================↑↑↑↑↑==== [deleted] ====↑↑↑↑↑=================================== */

  LocalViewMatch *vtm;
  int vt_window_width, vt_window_height;
};

}; // namespace ratslam

#endif /* VIEW_TEMPLATE_SCENE_HPP_ */
