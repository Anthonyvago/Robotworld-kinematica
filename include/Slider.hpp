/**
 * @file Slider.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-09
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef SLIDER_HPP
#define SLIDER_HPP

#include "Config.hpp"
#include "Widgets.hpp"

#include <functional>
#include <string>

namespace Application {
/**
 * Utility function that creates a Slider with min and max value that binds the
 * given ActionFunction with the wxEVT_SCROLL_THUMBRELEASE of the slider.
 *
 * @tparam ActionFunction
 * @param parent
 * @param minVal
 * @param maxVal
 * @param actionFunc
 * @return
 */
template <typename ActionFunction>
Slider *makeSlider(Window *parent, int32_t minVal, int32_t maxVal,
                   const ActionFunction actionFunc) {
  Slider *slider =
      new Slider(parent, DEFAULT_ID, 0, minVal, maxVal, wxDefaultPosition,
                 wxDefaultSize, wxSL_HORIZONTAL | wxSL_VALUE_LABEL);
  slider->Bind(wxEVT_SCROLL_THUMBRELEASE, actionFunc);
  return slider;
}

} // End of namespace Application

#endif // End of SLIDER_HPP