/******************************************************************************
* view.cpp
* Copyright 2010 Iain Peet
*
* Provides RayView classes, which trace a number of rays to render an image.
* Also provides the ViewObjectList class, which maintains a list of objects
* which might be seen in a RayView.
******************************************************************************
* This program is distrib
    $(COMMON_OBJS) \uted under the of the GNU Lesser Public License. 
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

#include <vector>
#include <iputil/trace.h>

#include "view.h"

#include "geom.h"
#include "image.h"
#include "ray.h"
#include "rayObject.h"
#include "world.h"

using std::vector;

static trc_ctl_t viewTrace = {
    TRC_DTL,
    "VIEW",
    TRC_STDOUT
};
#define TRACE(level,args...) \
    trc_printf(&viewTrace,level,1,args)

//! Render the given image using the given object list
void ParallelView::render(RayImage* image, World *world)
{
    char trcbuf[36];  // for trace messages
    
    // Create reference to image, for convenience
    RayImage & rImage = *image;
    
    Ray r;
    r.m_dir = m_xVec.cross(m_yVec).unitify();
    TRACE(TRC_STAT,"Beginning ParallelView render.\n");
    TRACE(TRC_STAT,"Image size: %d x %d\n",rImage.width(),rImage.height());
    TRACE(TRC_STAT,"Origin: %s\n",m_origin.snprint(trcbuf,36));
    TRACE(TRC_STAT,"xVec: %s\n",m_xVec.snprint(trcbuf,36));
    TRACE(TRC_STAT,"yVec: %s\n",m_yVec.snprint(trcbuf,36));
    TRACE(TRC_STAT,"Ray direction: %s\n",r.m_dir.snprint(trcbuf,36));

    /* Render the image */
    for(int i=0; i<rImage.width(); i+=1) {
        for(int j=0; j<rImage.height(); j+=1) {
	    r.m_endpoint = m_origin 
	        + ((double)i/rImage.width())*m_xVec
	        + ((double)j/rImage.height())*m_yVec;
	    TRACE(TRC_INFO,"Pixel endpoint: %s\n",
		  r.m_endpoint.snprint(trcbuf,36));
	    world->trace(&r);
	    rImage[i][j] = r.m_colour;
	    TRACE(TRC_INFO,"Render [%d,%d]: %s\n",
		  i,j,rImage[i][j].snprint(trcbuf,32));
	}
    }
}
