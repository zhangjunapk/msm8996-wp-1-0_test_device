#ifndef LAYOUT_MGR_H_
#define LAYOUT_MGR_H_

/** @file layout_manager.h
  @brief
  This file contains the interfaces to the Secure UI Layout Manager.
*/

/*===========================================================================
 Copyright (c) 2013-2015 Qualcomm Technologies, Inc.
 All Rights Reserved.
 Confidential and Proprietary - Qualcomm Technologies, Inc.
===========================================================================*/

/*===========================================================================

                      EDIT HISTORY FOR FILE

when       who     what, where, why
--------   ---     ----------------------------------------------------------
12/10/15   kl      (Tech Pubs) Comment updates for 80-NJ546-1 Rev. J.
10/27/15   gs	   Add rendering of the layouts bg image to a secure buffer
09/06/15   ls      Add documentation to all the external functions
03/09/15   sn      Changed the API to get the stride in each rendering.
08/03/15   ls      Add one-time per device keypad randomization.
11/10/13   sn      Initial Version.

===========================================================================*/
#include "SecureTouchLayout.h"

/*----------------------------------------------------------------------------
 * Type Declarations
 * -------------------------------------------------------------------------*/

/** @addtogroup layout_manager
@{ */

/** Layout manager return codes. */
typedef enum {
	LAYOUT_MGR_SUCCESS                        = 0,
	/**< Success. */
	LAYOUT_MGR_GENERAL_ERROR                  = -1,
	/**< General error.  */
	LAYOUT_MGR_BAD_LAYOUT                     = -2,
	/**< Received an invalid layout structure. */
	LAYOUT_MGR_GOT_NULL_INPUT                 = -3,
	/**< Received a null parameter. */
	LAYOUT_MGR_UNSUPPORTED                    = -4,
	/**< Operation is not supported with the specified parameters. */
	LAYOUT_MGR_OBJECT_NOT_FOUND               = -5,
	/**< The specified object does not exist in the layout.  */
	LAYOUT_MGR_TEXT_EXCEED_BUFFER             = -6,
	/**< Received text exceeds the given buffer size. */
	LAYOUT_MGR_UNEXPECTED_TIMEOUT             = -7,
	/**< An unexpected timeout event occurred.  */
	LAYOUT_MGR_BUTTON_BUSY                    = -8,
	/**< The button is currently in the pressed state, so it cannot be disabled. */
	LAYOUT_MGR_FAILED_GEN_RAND                = -9,
	/**< Random number generation failed. */
	LAYOUT_MGR_INVALID_UTF8_STR               = -10,
	/**< Received an invalid UTF8 string. */
	LAYOUT_MGR_TEXT_EXCEED_OBJECT             = -11,
	/**< Text exceeds the object size limitations.  */
	LAYOUT_MGR_UNCHANGED                      = -12,
	/**< No change occurred in the layout. */

	LAYOUT_MGR_ENTER_PRESSED                  = 1,
	/**< Function button 'enter' was pressed. */
	LAYOUT_MGR_CANCEL_PRESSED                 = 2,
	/**< Function button 'cancel' was pressed. */
	LAYOUT_MGR_F1_PRESSED                     = 3,
	/**< Function button F1 was pressed. */
	LAYOUT_MGR_F2_PRESSED                     = 4,
	/**< Function button F2 was pressed. */
	LAYOUT_MGR_F3_PRESSED                     = 5,
	/**< Function button F3 was pressed  */
    /** @cond */
	LAYOUT_MGR_ERR_SIZE                       = 0x7FFFFFFF
	/**< @endcond */
} layout_mgr_err_t;

/** Event type. */
typedef enum {
	TIMEOUT_EVENT,  /**< Timeout event. */
	TOUCH_EVENT,    /**< Touch event. */
	 /** @cond */
	EVENT_SIZE      = 0x7FFFFFFF
	/**< @endcond */
} event_t;

/*----------------------------------------------------------------------------
 * Function Declarations and Documentation
 * -------------------------------------------------------------------------*/

/*****************************************************************************************************************/

/**
   External function that loads a layout struct and screen properties and checks
   its validity. The function also sets some initial values.
   This function must be called before using any other API functions in this
   header file.

   @param[in] layoutPage   TUI screen layout that statically represents the
                           appearance of the screen. This layout is validated
                           and loaded on the screen.
   @param[in] screenHeight Device screen height, in pixels.
   @param[in] screenWidth  Device screen width, in pixels.
   @param[in] pixelWidth   Number of bytes representing 1 pixel.
   @param[in] timeout      Default timeout to be returned
                           if the Layout manager itself does not request a
                           different timeout for the operating the common
                           behavior of the layout; use NO_TIMEOUT if not
                           applicable.
   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_BAD_LAYOUT

   @dependencies
   None.
*/

layout_mgr_err_t layout_mgr_load_layout(LayoutPage_t* layoutPage, uint32_t screenHeight, uint32_t screenWidth, uint32_t pixelWidth, int32_t timeout);

/*****************************************************************************************************************/
/** @cond */
/**
   External function that updates the layout following a given touch or timeout
   event. This function outputs the current focused input object name, and
   the required timeout, in milliseconds, for the next timeout event. A timeout
   value of 0  means return immediately, and a value of -1 means
   no timeout at all.

   @param[in] event          Received touch or timeout event.
   @param[in] eventParams    Event parameters, for instance, the touch event
                             location parameters.
   @param[out] focusedInput  Current focused input object to be returned.
   @param[in] timeout        Timeout for the screen; 0 means return
                             immediately, -1 (NO_TIMEOUT) means no timeout at all.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_UNEXPECTED_TIMEOUT \n
   #LAYOUT_MGR_INVALID_UTF8_STR \n
   #LAYOUT_MGR_TEXT_EXCEED_BUFFER \n
   #LAYOUT_MGR_UNSUPPORTED

   @dependencies
   Must be called after layout_mgr_load_layout.

*/
layout_mgr_err_t layout_mgr_eval_event(event_t event, void* eventParams, const char** focusedInput, int32_t* timeout);


/*****************************************************************************************************************/

/**
   External function that wraps a call to the renderer to render the current
   layout to the given secure buffer.

   @param[in] secureBuffer  Secure buffer to which to render the layout.
   @param[in] screenStride  Actual width of the screen buffer.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_UNCHANGED \n
   #LAYOUT_MGR_TEXT_EXCEED_OBJECT \n
   #LAYOUT_MGR_BAD_LAYOUT

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_render_layout(uint8_t* secureBuffer, uint32_t screenStride);

/** @endcond */

/*****************************************************************************************************************/

/**
   External function that sets the buffer of the label of the specified object
   in the layout. Use the bSetDefaultLabel flag to set the default label of an
   input object. Note that this function does not set the text itself
   (curr_len is zeroed).

   @param[in] objectName       Object name (a unique identifier in the layout).
   @param[in] buffer           Buffer to be set for this object.
   @param[in] len              Length of the buffer.
   @param[in] bSetDefaultLabel Set to TRUE to set the default label of an input
                               object.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND

   @dependencies
   Must be called after layout_mgr_load_layout.

*/
layout_mgr_err_t layout_mgr_set_label_buffer(char* objectName, uint8_t* buffer, uint32_t len, uint32_t bSetDefaultLabel);

/*****************************************************************************************************************/

/**
   External function for setting the text of the label of a specified object in
   the layout. Use the bSetDefaultLabel flag to set the default label of an input
   object.

   @param[in] objectName        Object name (a unique identifier in the layout).
   @param[in] text              Text to set as the label.
   @param[in] len               Length of the text.
   @param[in] bSetDefaultLabel  Set to TRUE to set the default label of an input
                                object.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND \n
   #LAYOUT_MGR_TEXT_EXCEED_BUFFER \n
   #LAYOUT_MGR_INVALID_UTF8_STR

   @dependencies
   Must be called after layout_mgr_set_label_buffer.

*/
layout_mgr_err_t layout_mgr_set_label_text(char* objectName, uint8_t* text, uint32_t len, uint32_t bSetDefaultLabel);

/*****************************************************************************************************************/

/**
   External function for setting the display mode of a specified input object
   in the layout.

   @param[in] objectName  Object name (a unique identifier in the layout).
   @param[in] mode        Display mode to be set.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND \n
   #LAYOUT_MGR_UNSUPPORTED

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_set_input_display_mode(char* objectName, LayoutInputDisplayMode_t mode);

/*****************************************************************************************************************/

/**
   External function for setting the show flag of a specified object in the layout.

   @param[in] objectName   Object name (a unique identifier in the layout).
   @param[in] show         Show flag to be set.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_set_show_flag(char* objectName, uint8_t show);

/*****************************************************************************************************************/
/** @cond */
/**
   External function for setting the dirty bit of a specified object in the layout.

   @param[in] objectName   Object name (a unique identifier in the layout).
   @param[in] dirty        Dirty flag to be set.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_set_dirty_bit(char* objectName, uint8_t dirty);
/**@endcond */

/*****************************************************************************************************************/

/**
   External function for setting the state of a specified button object in the
   layout.

   @param[in] objectName   Object name (a unique identifier in the layout).
   @param[in] disabled     State of the button to be set.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND \n
   #LAYOUT_MGR_UNSUPPORTED \n
   #LAYOUT_MGR_BUTTON_BUSY

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_set_button_disabled(char* objectName, uint8_t disabled);

/*****************************************************************************************************************/

/**
   External function for setting focused input object in the layout.

   @param[in] objectName - Object name (as unique identifier in the layout)

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND \n
   #LAYOUT_MGR_UNSUPPORTED

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_set_focus_input(char* objectName);

/*****************************************************************************************************************/

/**
   External function for setting the image buffer and the alignment of a
   specified image object in the layout.

   @param[in] objectName   Object name (s unique identifier in the layout).
   @param[in] imageBuffer  Buffer that contains the PNG representation of the
                           required image.
   @param[in] vAlign       Vertical alignment.
   @param[in] hAlign       Horizontal alignment.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND \n
   #LAYOUT_MGR_UNSUPPORTED

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_set_image(char* objectName, uint8_t* imageBuffer, VerticalAlignment_t vAlign,HorizontalAlignment_t hAlign);

/*****************************************************************************************************************/

/**
   External function for setting the active keyboard in the layout.

   @param[in] keyboardName   Keyboard name to be set to active.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_set_active_keyboard(char* keyboardName);

/*****************************************************************************************************************/

/**
   External function for keyboard randomization in the layout.

   @param[in] keyboardName   Keyboard name to be randomized.
   @param[in] isOneTime      Set to TRUE if randomization is to be
                             one-time per device lifetime.
   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND \n
   #LAYOUT_MGR_UNSUPPORTED

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_randomize_keyboard(char* keyboardName, uint8_t isOneTime);

/*****************************************************************************************************************/

/**
   External function for getting the length of the text label of the specified
   input object in the layout. The length is returned in bytes and in
   characters.

   @param[in] objectName   Object name (a unique identifier in the layout).
   @param[out] chars_len   Lenght of the text lable, in UTF-8 characters.
   @param[out] bytes_len   Length of the text label, in bytes.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND \n
   #LAYOUT_MGR_INVALID_UTF8_STR

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_get_input_len(char* objectName, uint32_t* chars_len, uint32_t* bytes_len);

/*****************************************************************************************************************/

/**
   External function for setting the length of the text label of the specified
   input object in the layout. The label length must be smaller or equal to the
   given maximum length. The maximum length is in characters.

   @param[in] objectName      Object name (a unique identifier in the layout).
   @param[in] max_chars_len   Maximum text label length, in characters.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_set_input_len_to_max(char* objectName, uint32_t max_chars_len);

/*****************************************************************************************************************/

/**
   External function for deleting the last character of the focused input object.
   If there is no focused input, or in put is empty, nothing happens.

   @return
   None.

   @dependencies
   Must be called after layout_mgr_load_layout.
*/

void layout_mgr_delete_input_last_character(void);

/*****************************************************************************************************************/

/**
   External function for setting the buffer of an input object to zero.

   @param[in] objectName   Object name (as unique identifier in the layout)

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_OBJECT_NOT_FOUND

   @dependencies
   Must be called after layout_mgr_load_layout.
*/
layout_mgr_err_t layout_mgr_clear_input_buffer(char* objectName);


/*****************************************************************************************************************/

/** @cond */
/**
   @brief
   External function that wraps a call to the renderer to render the background
   of the current layout, to the specified secure buffer.

   @param[in] secureBuffer    Secure buffer to which to render the layout
                              background.
   @param[in] screenWidth     Width of the screen buffer.

   @return
   #LAYOUT_MGR_SUCCESS \n
   #LAYOUT_MGR_GOT_NULL_INPUT \n
   #LAYOUT_MGR_BAD_LAYOUT
*/
layout_mgr_err_t layout_mgr_render_bg_image(uint8_t** secureBuffer, uint32_t screenWidth);
/** @endcond */

/** @} */ /* end_addtogroup layout_manager */

#endif /* LAYOUT_MGR_H_ */
