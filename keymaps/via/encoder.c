 /* Copyright 2020 Josef Adamcik
  * Modification for VIA support and RGB underglow by Jens Bonk-Wiltfang
  * 
  * This program is free software: you can redistribute it and/or modify 
  * it under the terms of the GNU General Public License as published by 
  * the Free Software Foundation, either version 2 of the License, or 
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

//Setting up what encoder rotation does. If your encoder can be pressed as a button, that function can be set in Via.


#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 1, .col = 6}, .pressed = true, .time = (timer_read() | 1)  });  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 1, .col = 6}, .pressed = false, .time = (timer_read() | 1)  });
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 6}, .pressed = true, .time = (timer_read() | 1)  });
        	action_exec((keyevent_t){.key = (keypos_t){.row = 3, .col = 6}, .pressed = false, .time = (timer_read() | 1)  });  
            }
    } else if (index == 1) {
        if (clockwise) {  //Double check rotation on new flash versus via mapping
        	action_exec((keyevent_t){.key = (keypos_t){.row = 6, .col = 6}, .pressed = true, .time = (timer_read() | 1)  });  
        	action_exec((keyevent_t){.key = (keypos_t){.row = 6, .col = 6}, .pressed = false, .time = (timer_read() | 1)  });
        	} 
        	else {
        	action_exec((keyevent_t){.key = (keypos_t){.row = 8, .col = 6}, .pressed = true, .time = (timer_read() | 1)  });
        	action_exec((keyevent_t){.key = (keypos_t){.row = 8, .col = 6}, .pressed = false, .time = (timer_read() | 1)  });  
            }
    }
	return true;
}
#endif
