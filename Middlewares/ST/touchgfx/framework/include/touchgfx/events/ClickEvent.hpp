/******************************************************************************
* Copyright (c) 2018(-2021) STMicroelectronics.
* All rights reserved.
*
* This file is part of the TouchGFX 4.18.1 distribution.
*
* This software is licensed under terms that can be found in the LICENSE file in
* the root directory of this software component.
* If no LICENSE file comes with this software, it is provided AS-IS.
*
*******************************************************************************/

/**
 * @file touchgfx/events/ClickEvent.hpp
 *
 * Declares the touchgfx::ClickEvent class.
 */
#ifndef TOUCHGFX_CLICKEVENT_HPP
#define TOUCHGFX_CLICKEVENT_HPP

#include <touchgfx/hal/Types.hpp>
#include <touchgfx/Event.hpp>

namespace touchgfx
{
/**
 * A click event. The semantics of this event is slightly depending on hardware platform.
 * ClickEvents are generated by the HAL layer.
 *
 * @see Event
 */
class ClickEvent : public Event
{
public:
    /** Values that represent click event types. */
    enum ClickEventType
    {
        PRESSED,  ///< An enum constant representing the pressed option
        RELEASED, ///< An enum constant representing the released option
        CANCEL    ///< An enum constant representing the cancel option
    };

    /**
     * Initializes a new instance of the ClickEvent class.
     *
     * @param  type  The type of the click event.
     * @param  x     The x coordinate of the click event.
     * @param  y     The y coordinate of the click event.
     * @param  force (Optional) The force of the click. On touch displays this usually means how
     *               hard the user pressed on the display. On the windows platform, this
     *               will always be zero.
     */
    ClickEvent(ClickEventType type, int16_t x, int16_t y, int16_t force = 0)
        : clickEventType(type), clickX(x), clickY(y), clickForce(force)
    {
    }

    /**
     * Gets the x coordinate of this event.
     *
     * @return The x coordinate of this event.
     */
    int16_t getX() const
    {
        return clickX;
    }

    /**
     * Gets the y coordinate of this event.
     *
     * @return The y coordinate of this event.
     */
    int16_t getY() const
    {
        return clickY;
    }

    /**
     * Sets the x coordinate of this event.
     *
     * @param  x The x coordinate of this event.
     */
    void setX(int16_t x)
    {
        clickX = x;
    }

    /**
     * Sets the y coordinate of this event.
     *
     * @param  y The y coordinate of this event.
     */
    void setY(int16_t y)
    {
        clickY = y;
    }

    /**
     * Sets the click type of this event.
     *
     * @param  type The type to set.
     */
    void setType(ClickEventType type)
    {
        clickEventType = type;
    }

    /**
     * Gets the click type of this event.
     *
     * @return The click type of this event.
     */
    ClickEventType getType() const
    {
        return clickEventType;
    }

    /**
     * Gets the force of the click. On touch displays this usually means how hard the user
     * pressed on the display. On the windows platform, this will always be zero.
     *
     * @return The force of the click.
     */
    int16_t getForce() const
    {
        return clickForce;
    }

    /**
     * Gets event type.
     *
     * @return The type of this event.
     */
    virtual Event::EventType getEventType()
    {
        return Event::EVENT_CLICK;
    }

private:
    ClickEventType clickEventType;
    int16_t clickX;
    int16_t clickY;
    int16_t clickForce;
};

} // namespace touchgfx

#endif // TOUCHGFX_CLICKEVENT_HPP
