#ifndef INC_RC_INPUTSWITCH_H
#define INC_RC_INPUTSWITCH_H

/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** InputSwitch.h
** Class which takes input from the input buffer and acts like a switch
**
** Author: Daniel van den Ouden
** Project: ArduinoRCLib
** Website: http://sourceforge.net/p/arduinorclib/
** -------------------------------------------------------------------------*/

#include <inttypes.h>

#include <InputProcessor.h>
#include <SwitchSource.h>


namespace rc
{

/*! 
 *  \brief     Class which takes input from the input buffer and acts like a switch.
 *  \details   Takes input from the input buffer and writes to the switch buffer.
 *  \author    Daniel van den Ouden
 *  \date      Nov-2012
 *  \copyright Public Domain.
 */
class InputSwitch : public InputProcessor, public SwitchSource
{
public:
	/*! \brief Constructs an InputSwitch object
	    \param p_source Index to use as source input.
	    \param p_destination Switch to use as destination.
	    \param p_tri Tri state or bi state.*/
	InputSwitch(Input p_source = Input_None, Switch p_destination = Switch_None, bool p_tri = false);
	
	/*! \brief Sets the mark at which input should be considered Up position.
	    \param p_mark Mark to set.
	    \note default = 0 for bi state, 128 for tri state.*/
	void setUpMark(int16_t p_mark);
	
	/*! \brief Gets the mark at which input should be considered Up position.
	    \return Up mark.*/
	int16_t getUpMark() const;
	
	/*! \brief Sets the mark at which input should be considered Center position.
	    \param p_mark Mark to set.
	    \note default = 0 for bi state, -128 for tri state.*/
	void setCenterMark(int16_t p_mark);
	
	/*! \brief Gets the mark at which input should be considered Center position.
	    \return Center mark.*/
	int16_t getCenterMark() const;
	
	/*! \brief Reads and processes.
	    \param p_value Input value, range [-256 - 256].
	    \return Current switch state.*/
	SwitchState read(int16_t p_value) const;
	
	/*! \brief Reads and processes.
	    \return Current switch state.*/
	SwitchState read() const;
	
private:
	int16_t m_up;     //!< Up mark
	int16_t m_center; //!< Center mark
};
/** \example inputswitch_example.pde
 * This is an example of how to use the InputSwitch class.
 */


} // namespace end

#endif // INC_RC_INPUTSWITCH_H
