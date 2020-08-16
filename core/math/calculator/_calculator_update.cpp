#include "framework.h"
#include "core/math/calculator/calculator.h"
#include "aura/update.h"
#include "aura/const/id.h"


namespace calculator
{


   void plain_edit_view::update(::update * pupdate)
   {

      if (pupdate->m_id == id_after_change_text)
      {

         {

            sync_lock sl(m_pcallback == nullptr ? nullptr : m_pcallback->get_mutex());

            string strExp;

            _001GetText(strExp);

            parser parser(get_context_object());

            error e;

            e.m_iEnd = -1;
            e.m_iStart = -1;
            e.m_tick.Now();

            ::calculator::element * pelement = nullptr;

            string strSource;

            if (str::ends_eat_ci(strExp, "FPS"))
            {
               strSource = "Hz";
            }
            else if (str::ends_eat_ci(strExp, "Frames Per Second"))
            {
               strSource = "Hz";
            }
            else if (str::ends_eat_ci(strExp, "SPF"))
            {
               strSource = "s";
            }
            else if (str::ends_eat_ci(strExp, "Seconds per frame"))
            {
               strSource = "s";
            }
            else if (str::ends_eat_ci(strExp, "Hz"))
            {
               strSource = "Hz";
            }
            else if (str::ends_eat_ci(strExp, "minute"))
            {
               strSource = "min";
            }
            else if (str::ends_eat_ci(strExp, "days"))
            {
               strSource = "day";
            }
            else if (str::ends_eat_ci(strExp, "minutes"))
            {
               strSource = "min";
            }
            else if (str::ends_eat_ci(strExp, "hours"))
            {
               strSource = "hour";
            }
            else if (str::ends_eat_ci(strExp, "hour"))
            {
               strSource = "hour";
            }
            else if (str::ends_eat_ci(strExp, "day"))
            {
               strSource = "day";
            }
            else if (str::ends_eat_ci(strExp, "ms"))
            {
               strSource = "ms";
            }
            else if (str::ends_eat_ci(strExp, "s"))
            {
               strSource = "s";
            }
            else
            {
               strSource = m_strFormat;
            }
            string strFormat(m_strFormat);

            if (str::ends_eat_ci(strFormat, "FPS"))
            {
               strFormat = "Hz";
            }
            else if (str::ends_eat_ci(strFormat, "Frames Per Second"))
            {
               strFormat = "Hz";
            }
            else if (str::ends_eat_ci(strFormat, "SPF"))
            {
               strFormat = "s";
            }
            else if (str::ends_eat_ci(strFormat, "Seconds per frame"))
            {
               strFormat = "s";
            }
            else if (str::ends_eat_ci(strFormat, "Hz"))
            {
               strFormat = "Hz";
            }
            else if (str::ends_eat_ci(strFormat, "s"))
            {
               strFormat = "s";
            }
            else
            {
               strFormat = m_strFormat;
            }
            strExp.trim();
            try
            {

               pelement = parser.parse(strExp);
               //__throw(::exception::exception("now a simple exception here"));

            }
            catch (const numeric_parser_exception & exp)
            {

               e.m_strMessage = exp.get_message();
               e.m_iStart = 0;
               e.m_iEnd = strExp.length();

            }

            string str;

            if (pelement != nullptr)
            {

               m_val = pelement->get_value();

               str = strExp;

            }

            string strVal;
            bool bConv = true;

            if (e.m_iStart < 0)
            {

               if (strSource.has_char())
               {
                  if (strSource != strFormat)
                  {

                     if (strFormat == "s")
                     {
                        if (strSource == "Hz")
                        {
                           if (m_val.mod() == 0.0)
                           {
                              strVal = "(infinite)";
                           }
                           else
                           {
                              strVal = __str(1.0 / m_val.mod());
                           }
                        }
                     }
                     else if (strFormat == "Hz")
                     {
                        if (m_val.mod() == 0.0)
                        {
                           strVal = "(infinite)";
                        }
                        else if (strSource == "ms")
                        {
                           m_val.m_dR = 1000.0 / m_val.m_dR;
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else if (strSource == "s")
                        {
                           m_val.m_dR = 1.0 / m_val.m_dR;
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else if (strSource == "min")
                        {
                           m_val.m_dR = 1.0 / (60.0 * m_val.m_dR);
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();

                        }
                        else if (strSource == "hour")
                        {
                           m_val.m_dR = 1.0 / (60.0 * 60.0 * m_val.m_dR);
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else if (strSource == "day")
                        {
                           m_val.m_dR = 1.0 / (24.0 * 60.0 * 60.0 * m_val.m_dR);
                           m_val.m_dI = 0.0;
                           strVal = m_val.to_string();
                        }
                        else
                        {
                           strVal = m_val.to_string();
                        }
                     }

                  }
               }
               else
               {
                  e.m_strMessage = "(unknown conversion)";
                  bConv = false;
                  strVal = m_val.to_string();
               }
            }
            else
            {
               strVal = m_val.to_string();
            }

            if (!bConv)
            {
               e.m_iStart = (strExp + string(" ")).length();
               e.m_iEnd = e.m_iStart + strSource.length();

            }
            str = strExp + string(" ") + strSource + string(" = ") + strVal;

            if (m_pcallback != nullptr)
            {

               if (m_strFormat.has_char())
               {

                  m_pcallback->set_expression(str + " " + m_strFormat);

               }
               else
               {

                  m_pcallback->set_expression(str);

               }

            }

            if (e.m_iStart >= 0)
            {
               m_errora.add(e);
            }
            else
            {
               m_errora.remove_all();
            }


         }

         /*         if(m_ptopview != nullptr)
                  {

                     m_ptopview->m_pview->post_message(message_view_update);

                  }*/

      }

   }

   
void plain_edit_view::plain_edit_on_after_change_text(::draw2d::graphics_pointer & pgraphics, const ::action_context & context)
   {

      if (context.is_user_source())
      {


         //      if(m_ptopview == nullptr || m_ptopview->m_pview == nullptr)
         //       return;

         call_update(id_after_change_text);

      }

      plain_edit::plain_edit_on_after_change_text(pgraphics, context);

   }



} // namespace calculator

