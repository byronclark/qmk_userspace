// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#if defined(RGB_MATRIX_ENABLE)
#define RGB_MATRIX_KEYRELEASES
#define ENABLE_RGB_MATRIX_SOLID_SPLASH

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_SPLASH

#define RGB_MATRIX_DEFAULT_HUE 191
#define RGB_MATRIX_DEFAULT_SAT 255
#define RGB_MATRIX_DEFAULT_VAL 150

#endif

// Turn off ErgoDox EZ extra features.
// No effect for other boards.
#undef ORYX_CONFIGURATOR
#undef ORYX_ENABLE
