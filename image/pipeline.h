/******************************************************************************
 * pipeline.h
 * Copyright 2011 Iain Peet
 *
 * The ImagePipeline class composes all of the image processing operations 
 * required to transform a traced RayImage into an image suitable for
 * display.
 ******************************************************************************
 * This program is distributed under the of the GNU Lesser Public License. 
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *****************************************************************************/

#ifndef IMAGE_PIPELINE_H_
#define IMAGE_PIPELINE_H_

#include <vector>
#include <memory>

class Image;
class ImageSize;
class ImageTransform;
class RayImage;
class Resampler;

class ImagePipeline {
private:
  // Sequence of transforms to apply to the render
  std::vector<ImageTransform*> m_transforms;

  // Used to resize the final image, if requested.
  std::auto_ptr<Resampler>     m_resampler;

public:
  ImagePipeline() :
    m_transforms(), m_resampler(0)
    { /* n/a */ }
  ~ImagePipeline();

  // Adds another transform to the pipeline
  void push(std::auto_ptr<ImageTransform> transform);

  // Set the resampler used to resize the final image, if requested.
  void setResampler(std::auto_ptr<Resampler> resampler);

  /* Processes the given traced RayImage through the image pipeline.
   * Returned Image will have whatever resolution the pipeline produces
   * for the resolution of the given RayImage */
  std::auto_ptr<Image> process(const RayImage& img);

  /* Processes the given traced RayImage through the image pipeline.
   * If the result of the pipeline does not have the given width
   * and height, the resampler set with setResampler will be used
   * to resample to the desired resolution. */
  std::auto_ptr<Image> process
      (const RayImage& img, const ImageSize &size);
};

#endif //IMAGE_PIPELINE_H_

