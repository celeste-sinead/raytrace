/******************************************************************************
 * imagePipeline.cpp
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

#include "pipeline.h"

#include "image.h"
#include "transform.h"
#include "rayImage.h"
#include "resample.h"

using namespace std;
using namespace std::tr1;

ImagePipeline::~ImagePipeline() {
	for (unsigned i=0; i<m_transforms.size(); ++i) {
		delete m_transforms[i];
	}
}

void ImagePipeline::push(auto_ptr<ImageTransform> transform) {
	/* The purpose of the auto_ptr is to hint strongly to the client
	 * that the transform is to be dynamically allocated, with ownership
	 * passed to the pipeline.  Once ownership is taken, the auto_ptr
	 * is stripped, since it won't play nice with vectors */
	m_transforms.push_back(transform.release());
}

void ImagePipeline::setResampler(auto_ptr<Resampler> resampler) {
	m_resampler = resampler;
}

shared_ptr<Image> ImagePipeline::process(const RayImage &img) {
	shared_ptr<Image> ret (new Image());
	ret->fromRay(img);

	for (unsigned i=0; i < m_transforms.size(); ++i) {
		m_transforms[i]->apply(*ret);
	}

	return ret;
}

shared_ptr<Image> ImagePipeline::process
		(const RayImage& img, unsigned width, unsigned height) 
{
	shared_ptr<Image> ret = process(img);

	if (!m_resampler.get()) {
		// No resampler set, can't resize.
		return ret;
	}

	if ((width != ret->width()) || (height != ret->height())) {
		// Need to resample the output image
		m_resampler->setResolution(width, height);
		m_resampler->apply(*ret);
	}

	return ret;
}

