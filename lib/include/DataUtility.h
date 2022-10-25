#pragma once


namespace rf
{
class Contour;

class DataUtility 
{
public:


/**
 * @brief Checks  if the contour direction is correct
 * 
 * @param contour 
 * @return true - for correct direction
 * @return false - for wrong direction
 */
 static bool CheckIsContourDirectionCorrect(const Contour& contour);
 

 /**
  * @brief Corrects the contour direction if it is not correct for the given type of contour
  * 
  * @param contour 
  */
 static void ReverseIfContourWrongDirection(Contour& contour);
private:
};
} // namespace rf
