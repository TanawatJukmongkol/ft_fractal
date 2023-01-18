/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_codes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 04:50:18 by tjukmong          #+#    #+#             */
/*   Updated: 2023/01/19 05:23:49 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_CODES_H
# define EVENT_CODES_H

# ifdef __linux__
#  include <X11/keysym.h>

// 0 = no key assigned
// kdef_ = key defines
// kmod_ = moded key combinations
enum	e_keydef {
	kdef_term	= XK_Escape,
	kdef_mod	= XK_Control_L,
	kdef_up		= XK_Up,
	kdef_down	= XK_Down,
	kdef_left	= XK_Left,
	kdef_right	= XK_Right,
	kmod_origin	= XK_o,
	kmod_color	= XK_Shift_L
};

enum	e_mousedef {
	mouse_Left			= 1,
	mouse_Middle		= 2,
	mouse_Rright		= 3,
	mouse_Middle_Up		= 4,
	mouse_Middle_Down	= 5
};

# else

enum	e_osxkeys {
	OSXK_a					= 0x00
	OSXK_s					= 0x01
	OSXK_d					= 0x02
	OSXK_f					= 0x03
	OSXK_h					= 0x04
	OSXK_g					= 0x05
	OSXK_z					= 0x06
	OSXK_x					= 0x07
	OSXK_c					= 0x08
	OSXK_v					= 0x09
	OSXK_b					= 0x0b
	OSXK_q					= 0x0c
	OSXK_w					= 0x0d
	OSXK_e					= 0x0e
	OSXK_r					= 0x0f
	OSXK_y					= 0x10
	OSXK_t					= 0x11
	OSXK_1					= 0x12
	OSXK_2					= 0x13
	OSXK_3					= 0x14
	OSXK_4					= 0x15
	OSXK_6					= 0x16
	OSXK_5					= 0x17
	OSXK_Equal				= 0x18
	OSXK_9					= 0x19
	OSXK_7					= 0x1a
	OSXK_Minus				= 0x1b
	OSXK_8					= 0x1c
	OSXK_0					= 0x1d
	OSXK_Braceright			= 0x1e
	OSXK_o					= 0x1f
	OSXK_u					= 0x20
	OSXK_Braceleft			= 0x21
	OSXK_i					= 0x22
	OSXK_p					= 0x23
	OSXK_Return				= 0x24
	OSXK_l					= 0x25
	OSXK_j					= 0x26
	OSXK_Singlelowquotemark	= 0x27
	OSXK_k					= 0x28
	OSXK_Semicolon			= 0x29
	OSXK_Backslash			= 0x2a
	OSXK_Comma				= 0x2b
	OSXK_Slash				= 0x2c
	OSXK_n					= 0x2d
	OSXK_m					= 0x2e
	OSXK_Period				= 0x2f
	OSXK_Tab				= 0x30
	OSXK_Space				= 0x31
	OSXK_Tilde				= 0x32
	OSXK_Delete				= 0x33
	OSXK_Escape				= 0x35
	OSXK_Command			= 0x37
	OSXK_Shift_L			= 0x38
	OSXK_Capslock			= 0x39
	OSXK_Option_L			= 0x34
	OSXK_Control_L			= 0x34
	OSXK_Keypad_Period		= 0x41
	OSXK_Keypad_Asterisk	= 0x43
	OSXK_Keypad_Plus		= 0x45
	OSXK_Keypad_Slash		= 0x4B
	OSXK_Keypad_Enter		= 0x4C
	OSXK_Keypad_Minus		= 0x4E
	OSXK_Keypad_Equal		= 0x51
	OSXK_Keypad_0			= 0x52
	OSXK_Keypad_1			= 0x53
	OSXK_Keypad_2			= 0x54
	OSXK_Keypad_3			= 0x55
	OSXK_Keypad_4			= 0x56
	OSXK_Keypad_5			= 0x57
	OSXK_Keypad_6			= 0x58
	OSXK_Keypad_7			= 0x59
	OSXK_Keypad_8			= 0x5B
	OSXK_Keypad_9			= 0x5C
	OSXK_F5					= 0x60
	OSXK_F6					= 0x61
	OSXK_F7					= 0x62
	OSXK_F3					= 0x63
	OSXK_F8					= 0x64
	OSXK_F9					= 0x65
	OSXK_F11				= 0x67
	OSXK_F13				= 0x69
	OSXK_F14				= 0x6B
	OSXK_F10				= 0x6D
	OSXK_F12				= 0x6F
	OSXK_F15				= 0x71
	OSXK_Help				= 0x72
	OSXK_Home				= 0x73
	OSXK_PageUp				= 0x74
	OSXK_Delete_Under_Help	= 0x75
	OSXK_F4					= 0x76
	OSXK_End				= 0x77
	OSXK_F2					= 0x78
	OSXK_PageDown			= 0x79
	OSXK_F1					= 0x7A
	OSXK_LeftArrow			= 0x7B
	OSXK_RightArrow			= 0x7C
	OSXK_DownArrow			= 0x7D
	OSXK_UpArrow			= 0x7E
};

enum	e_keydef {
	kdef_term	= OSXK_Escape,
	kdef_mod	= OSXK_Control_L,
	kdef_up		= OSXK_Up,
	kdef_down	= OSXK_Down,
	kdef_left	= OSXK_Left,
	kdef_right	= OSXK_Right,
	kmod_origin	= OSXK_o,
	kmod_color	= OSXK_Shift_L
};

enum	e_mousedef {
	mouse_Left			= 1,
	mouse_Rright		= 2,
	mouse_Middle		= 3,
	mouse_Middle_Up		= 4,
	mouse_Middle_Down	= 5
};

# endif

enum	e_keybit {
	kbit_mod	= 0b00000001,
	kbit_up		= 0b00000010,
	kbit_down	= 0b00000100,
	kbit_left	= 0b00001000,
	kbit_right	= 0b00010000,
	kbit_origin	= 0b00100000,
	kbit_color	= 0b01000000
};

#endif