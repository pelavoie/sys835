/*	utils.h
 *
 * List of prototypes for used fonctions
 */



/************************************* Definitions **********************************************/
// TODO: Tables of besssel Functions and epsilon


/************************************* Prototypes ***********************************************/
float GetCalculatedSuppressionValue(unsigned int ulEpsilon, float lMeasuredParms);
float GetSmoothedSuppressionValue(float lCurrentGain, float lPreviousGain);
void RecombineSignal( float* lResultData, float* lChannelData, unsigned int ulNbData, unsigned int ulChannelNumber);
