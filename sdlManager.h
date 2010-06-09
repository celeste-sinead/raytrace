/******************************************************************************
* sdlManager.h
* Copyright 2010 Iain Peet
*
* Provides a singleton class which contols global SDL state - primarily
* initialization and finalization.
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

#ifndef sdl_manager_h_
#define sdl_manager_h_

class SDLManager {
private:
    //! Whether or not SDL has been initialized successfully
    bool m_isReady;
    
public:
    //! Get singleton instance
    static SDLManager & instance();
    
    //! Checks if SDL is ready to use.  (False if initialization failed)
    bool isReady() const 
	{ return m_isReady; }
    
private:
    //! Initializes SDL
    SDLManager();
 
    /** atexit function, which finalizes SDL. */
    static void sdlFinalizer();
    
};

#endif // sdl_manager_h_
