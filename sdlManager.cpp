/******************************************************************************
* sdlManager.cpp
* Copyright 2010 Iain Peet
*
* Implements the SDLManager singleton, which is responsible for global SDL
* state.
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
****************************************************************************/

#include <cstdlib>
#include <SDL/SDL.h>
#include <iputil/trace.h>

#include "sdlManager.h"

//! Set up tracing
static trc_ctl_t sdlMgrTrace = {
    TRC_DTL, //TRC_DFL_LVL,
    "SDL",
    TRC_STDOUT
};
#define TRACE(level, args...) \
    trc_printf(&sdlMgrTrace,level,1,args)

//! The singleton instance
static SDLManager * mgrInst = 0;

//! Get the singleton
SDLManager& SDLManager::instance()
{
    if( !mgrInst ) {
	mgrInst = new SDLManager();
    }
    if( !mgrInst ) {
	TRACE(TRC_ERR,"Failed to allocate a SDLManager.\n");
	abort();
    }
    return *mgrInst;
}

//! Initialize SDL 
SDLManager::SDLManager()
{
    TRACE(TRC_INFO,"Instantiating SDLManager\n");
    
    if( SDL_Init( SDL_INIT_VIDEO ) == -1 ) {
	TRACE(TRC_ERR,"Failed to initialize SDL: %s\n",SDL_GetError());
	m_isReady = false;
    } else {
	TRACE(TRC_STAT,"SDL initialized successfully.\n");
	m_isReady = true;
	//! Want to finalize only at program exit
	atexit(SDLManager::sdlFinalizer);
    }
}

//! Finalize SDL 
void SDLManager::sdlFinalizer() {
    TRACE(TRC_STAT,"Finalizing SDL...\n");
    SDL_Quit();   
}
