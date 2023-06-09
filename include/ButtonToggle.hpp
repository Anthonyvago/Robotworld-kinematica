/**
 * @file ToggleButton.hpp
 * @author Anthony Vago (A.Vago@student.han.nl)
 * @brief
 * @version 0.1
 * @date 2023-06-03
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef BUTTONTOGGLE_HPP
#define BUTTONTOGGLE_HPP

#include "Config.hpp"
#include "Widgets.hpp"

#include <functional>
#include <string>

namespace Application {
/**
 * Utility function that creates a ToggleButton with label that binds the given
 * ActionFunction with the wxEVT_COMMAND_TOGGLEBUTTON_CLICKED of the button.
 *
 * @tparam ActionFunction
 * @param aParent
 * @param label
 * @param actionSymbol
 * @return
 */
template <typename ActionFunction>
ToggleButton *makeToggleButton(Window *parent, const std::string &label,
                               const ActionFunction actionSymbol) {
  ToggleButton *button = new ToggleButton(parent, DEFAULT_ID, WXSTRING(label));
  button->Bind(wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, actionSymbol);
  return button;
}
} // End of namespace Application

#endif // End of BUTTONTOGGLE_HPP
