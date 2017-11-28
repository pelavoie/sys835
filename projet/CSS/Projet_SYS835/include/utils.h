/*	utils.h
 *
 * List of prototypes for used fonctions
 */



/************************************* Definitions **********************************************/
// TODO: Tables of besssel Functions and epsilon


/************************************* Prototypes ***********************************************/

/* GetCalculatedSuppressionValue
 *
 * 		arguments:
 * 			- ulEpsilon: Epsilon
 * 			- lMeasuredParms : Measured parameters.
 * 		Description:
 * 			it choose the proper Suppression table (according to ulEpsilon)
 * 			and determine the value of Suppression with lMeasuredParms
 * 		returns:
 * 			- (float) Pre-calculated value of suppression Gain.
 */
float GetCalculatedSuppressionValue(const unsigned int ulEpsilon, const float lMeasuredParms);

/* GetSmoothedSuppressionValue
 *
 * 		arguments:
 * 			- lCurrentGain: The current calculated Gain
 * 			- lPreviousGain : The last applied Gain.
 * 		Description:
 * 			it "smooth" the current calculated gain to minimize brutal variations.
 * 		returns:
 * 			- (float) Smoothed value of suppression to apply.
 */
float GetSmoothedSuppressionValue(const float lCurrentGain, const float lPreviousGain);

/* GetSmoothedSuppressionValue
 *
 * 		arguments:
 * 			- lResultData: Pointer of the Result Array of float data
 * 			- lChannelData : Pointer of the Channel Array of float data
 * 			- ulNbData : Number of Data in the Arrays
 * 			- ulChannelNumber : the number of the channel
 * 		Description:
 * 			it add or substract (depending of the channel number) the lChannelData arrays to
 * 			the lResultData Arrays. The size of lResultData must be the same as lChannelData. *
 * 		returns:
 * 			- void, the lResultData arrays is "modified" to the new result.
 */
void RecombineSignal(const float* lResultData, const float* lChannelData, const unsigned int ulNbData, const unsigned int ulChannelNumber);
