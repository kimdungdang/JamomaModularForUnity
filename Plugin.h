//
//  Plugin.h
//  BundleUnity
//

// NOTE : IL FAUT REVOIR "mDataDemoMessage"


/** @file
 *
 * @ingroup Jamoma Modular Library
 *
 * @brief This is a plugin for Unity using the Jamoma Modular library (file .H)
 *
 * @details This plugin allows the communication between i-score and video games created by Unity
 *
 * @authors Kim Dung Dang and Théo de la Hogue (created by Kim Dung Dang on 26/03/2014)
 *
 * @copyright © 2014 CNAM and GMEA, all rights reserved @n
 *
 */



#ifndef BundleUnity_Plugin_h
#define BundleUnity_Plugin_h

#include "TTModular.h"
#include <vector>

extern "C"
{
    ///< Callback function (used in Unity) which allows informing the mocification of value of a data
    typedef void (__stdcall * ValueCallback)();
    
    // Declare the application manager, the local application and the distant application
    TTObject mApplicationManager;   ///< The application manager of the Jamoma Modular framework
    TTObject mApplicationLocal;     ///< The local application is Unity
    TTObject mApplicationDistant;   ///< The distant application is i-score
    
    // Declare a Minuit protocol unit to use
    TTObject mProtocolMinuit;       ///< The Minuit protocol allows the communication between i-score and Unity
    
    // Declare publicly all datas of the local application to retreive them from the callback function
    int numberParameterData = 0;            ///< Number of parameters communicated between i-score and Unity
    std::vector<TTObject> mDataParameterVector;   ///< Vector of parameters which are relative to the state of the local application and which are communicated between i-score and Unity, the length of this vector is "numberParameterData"
    
    int numberReturnData = 0;            ///< Number of returns communicated between i-score and Unity
    std::vector<TTObject> mDataReturnVector;   ///< Vector of returns which are communicated between i-score and Unity (a return is a kind of notification sent by Unity to i-score), the length of this vector is "numberReturnData"
    
    TTObject mDataDemoMessage;      ///< A message is a kind of command to send to Unity
    
    /** Callback function (used in C/C++) */
    void DataReturnValueCallback();
    
    /** Callback function (used in C/C++) to get data's value back
     @param[in] baton #TTValue
     @param[out] value #TTValue
    void DataReturnValueCallback(const TTValue& baton, const TTValue& value);
    */
    
    /** Init the Jamoma Modular library
     @param[in] folderPath Folder path where all the dylibs are */
    void InitModularLibraryPlugin (char folderPath[]);
    
    /** Create an application manager */
    void CreateApplicationManagerPlugin();
    
    /** Create a local application, a distant application and register them to the application manager
     @param[in] localAppName Name of the local application
     @param[in] distantAppName Name of the distant application
     @return 0: Cannot create the local application
     @return 1: Cannot create the distant application
     @return 2: Create the local and distant applications and register them successfully */
    int CreateAndRegisterApplicationsPlugin(char localAppName[], char distantAppName[]);
    
    /** Create a Minuit protocol unit
     @return 0: Cannot create the Minuit protocol unit
     @return 1: Create successfully the Minuit protocol unit */
    int CreateMinuitProtocolUnitPlugin();
    
    /** Register the local and distant applications to the Minuit protocol
	 @param[in] localAppName Name of the local application
	 @param[in] distantAppName Name of the distant application
	 @param[in] portLocal Port of the local application
	 @param[in] ipLocal IP adress of the local application
	 @param[in] portDistant Port of the distant application
	 @param[in] ipDistant IP adress of the distant application */
	void RegisterApplicationsToMinuitPlugin(char localAppName[], char distantAppName[], int portLocal, char ipLocal[], int portDistant, char ipDistant[]);
    
    /** Run the Minuit protocol */
    void RunMinuitProtocolPlugin();
    
    /** Set the author's name of the local application
     @param[in] authorName The author's name */
    void SetAuthorNamePlugin(char authorName[]);
    
    /** Get the author's name of the local application
     @return Author's name of the local application */
    const char* GetAuthorNamePlugin();
    
    /** Set the version name of the local application
     @param[in] versionName The version name of the local appliation */
    void SetVersionPlugin(char versionName[]);
    
    /** Get the version name of the local application
     @return Version name of the local application */
    const char* GetVersionPlugin();
    
    /** Create a parameter data (type "integer" or "decimal") at an address (without the callback function in Unity)
     @param[in] paramaterAddress Address of this parameter registered in the local application
     @param[in] type "type" attribute of this parameter
     @param[in] rangeBoundMin Min bound of the "rangeBounds" attribute of this parameter
     @param[in] rangeBoundMax Max bound of the "rangeBounds" attribute of this parameter
     @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
     @param[in] rampDrive "rampDrive" attribute of this parameter
     @param[in] description "description" attribute of this parameter
     @return 0: Cannot create the parameter data at this address
     @return 1: Create successfully the parameter data at this address */
    int CreateNumberParameterDataPlugin(char paramaterAddress[], char type[], float rangeBoundMin, float rangeBoundMax, char rangeClipmode[], char rampDrive[], char description[]);
    
    /** Create a parameter data (type "integer" or "decimal") at an address (with the callback function in Unity)
     @param[in] paramaterAddress Address of this parameter registered in the local application
     @param[in] type "type" attribute of this parameter
     @param[in] rangeBoundMin Min bound of the "rangeBounds" attribute of this parameter
     @param[in] rangeBoundMax Max bound of the "rangeBounds" attribute of this parameter
     @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
     @param[in] rampDrive "rampDrive" attribute of this parameter
     @param[in] description "description" attribute of this parameter
     @param[in] valueCallback The callback function corresponding to this parameter
     @return 0: Cannot create the parameter data at this address
     @return 1: Create successfully the parameter data at this address */
    int CreateNumberParameterDataPluginWithCallbackUnity(char paramaterAddress[], char type[], float rangeBoundMin, float rangeBoundMax, char rangeClipmode[], char rampDrive[], char description[], ValueCallback valueCallback);
    
    /** Create a parameter data (type "boolean") at an address (without the callback function in Unity)
     @param[in] paramaterAddress Address of this parameter registered in the local application
     @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
     @param[in] rampDrive "rampDrive" attribute of this parameter
     @param[in] description "description" attribute of this parameter
     @return 0: Cannot create the parameter data at this address
     @return 1: Create successfully the parameter data at this address */
    int CreateBooleanParameterDataPlugin(char paramaterAddress[], char rangeClipmode[], char rampDrive[], char description[]);
    
    /** Create a parameter data (type "boolean") at an address (with the callback function in Unity)
     @param[in] paramaterAddress Address of this parameter registered in the local application
     @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
     @param[in] rampDrive "rampDrive" attribute of this parameter
     @param[in] description "description" attribute of this parameter
     @param[in] valueCallback The callback function corresponding to this parameter
     @return 0: Cannot create the parameter data at this address
     @return 1: Create successfully the parameter data at this address */
    int CreateBooleanParameterDataPluginWithCallbackUnity(char paramaterAddress[], char rangeClipmode[], char rampDrive[], char description[], ValueCallback valueCallback);
    
    /** Create a parameter data (type "string") at an address (without the callback function in Unity)
     @param[in] paramaterAddress Address of this parameter registered in the local application
     @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
     @param[in] rampDrive "rampDrive" attribute of this parameter
     @param[in] description "description" attribute of this parameter
     @return 0: Cannot create the parameter data at this address
     @return 1: Create successfully the parameter data at this address */
    int CreateStringParameterDataPlugin(char paramaterAddress[], char rangeClipmode[], char rampDrive[], char description[]);
    
    /** Create a parameter data (type "string") at an address (with the callback function in Unity)
     @param[in] paramaterAddress Address of this parameter registered in the local application
     @param[in] rangeClipmode "rangeClipmode" attribute of this parameter
     @param[in] rampDrive "rampDrive" attribute of this parameter
     @param[in] description "description" attribute of this parameter
     @param[in] valueCallback The callback function corresponding to this parameter
     @return 0: Cannot create the parameter data at this address
     @return 1: Create successfully the parameter data at this address */
    int CreateStringParameterDataPluginWithCallbackUnity(char paramaterAddress[], char rangeClipmode[], char rampDrive[], char description[], ValueCallback valueCallback);
    
    /** Create a return data at an address (without the callback function in Unity)
     @param[in] returnAddress Address of this return registered in the local application
     @param[in] type "type" attribute of this return (type is "decimal" or "integer" or "boolean")
     @param[in] description "description" attribute of this return
     @return 0: Cannot create the return data at this return
     @return 1: Create successfully the return data at this address */
    int CreateReturnDataPlugin(char returnAddress[], char type[], char description[]);
    
    /** Create a return data at an address (with the callback function in Unity)
     @param[in] returnAddress Address of this return registered in the local application
     @param[in] type "type" attribute of this return (type is "decimal" or "integer" or "boolean")
     @param[in] description "description" attribute of this return
     @param[in] valueCallback The callback function corresponding to this parameter
     @return 0: Cannot create the return data at this return
     @return 1: Create successfully the return data at this address */
    int CreateReturnDataPluginWithCallbackUnity(char returnAddress[], char type[], char description[], ValueCallback valueCallback);
    
    /** Create a message data at an address (without the callback function in Unity)
     @param[in] messageAddress Address of this message registered in the local application
     @param[in] type "type" attribute of this message
     @param[in] description "description" attribute of this message
     @return 0: Cannot create the message data at this address
     @return 1: Create successfully the message data at this address */
    int CreateMessageDataPlugin(char messageAddress[], char type[], char description[]);
    
    /** Create a message data at an address (with the callback function in Unity)
     @param[in] messageAddress Address of this message registered in the local application
     @param[in] type "type" attribute of this message
     @param[in] description "description" attribute of this message
     @param[in] valueCallback The callback function corresponding to this message
     @return 0: Cannot create the message data at this address
     @return 1: Create successfully the message data at this address */
    int CreateMessageDataPluginWithCallbackUnity(char messageAddress[], char type[], char description[], ValueCallback valueCallback);
    
    /** Setup the control of i-score from an external Tick message */
    void SetupMessageTickPlugin();
    
    /** Send a Tick message to i-score to control it */
    void SendMessageTickPlugin();
    
    /** Set a new value for an attribute of a parameter (only applied to "type, rangeClipmode, rampDrive, description" attributes)
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @param[in] nameAttribute Name of this attribute
     @param[in] newValue The new value set to this attribute */
    void SetAttributeParameterPlugin(int indexParameter, char nameAttribute[], char newValue[]);
    
    /** Get the current value of an attribute of a parameter (only applied to "type, rangeClipmode, rampDrive, description" attributes)
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @param[in] nameAttribute Name of this attribute
     @return Current value of this attribute */
    const char* GetAttributeParameterPlugin(int indexParameter, char nameAttribute[]);
    
    /** Set a new value for the "rangeBounds" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @param[in] rangeBoundMin Min bound of the "rangeBounds" attribute of the new value
     @param[in] rangeBoundMax Max bound of the "rangeBounds" attribute of the new value */
    void SetRangeBoundsParameterPlugin(int indexParameter, float rangeBoundMin, float rangeBoundMax);
    
    /** Get the current value of the min bound of the "rangeBounds" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @return Current value of the min bound of the "rangeBounds" attribute of this parameter */
    float GetMinRangeBoundParameterPlugin(int indexParameter);
    
    /** Get the current value of the max bound of the "rangeBounds" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @return Current value of the max bound of the "rangeBounds" attribute of this parameter */
    float GetMaxRangeBoundParameterPlugin(int indexParameter);
    
    /** Set a new value (type "decimal") for the "value" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @param[in] newValue The new value set to this attribute */
    void SetValueFloatParameterPlugin(int indexParameter, float newValue);
    
    /** Set a new value (type "integer") for the "value" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @param[in] newValue The new value set to this attribute */
    void SetValueIntegerParameterPlugin(int indexParameter, int newValue);
    
    /** Set a new value (type "boolean") for the "value" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @param[in] newValue The new value set to this attribute */
    void SetValueBooleanParameterPlugin(int indexParameter, bool newValue);
    
    /** Set a new value (type "string") for the "value" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @param[in] newValue The new value set to this attribute */
    void SetValueStringParameterPlugin(int indexParameter, char newValue[]);
    
    /** Get the current value (type "decimal") of the "value" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @return Current value of the "value" attribute of this parameter */
    float GetValueFloatParameterPlugin(int indexParameter);
    
    /** Get the current value (type "integer") of the "value" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @return Current value of the "value" attribute of this parameter */
    int GetValueIntegerParameterPlugin(int indexParameter);
    
    /** Get the current value (type "boolean") of the "value" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @return Current value of the "value" attribute of this parameter */
    bool GetValueBooleanParameterPlugin(int indexParameter);
    
    /** Get the current value (type "string") of the "value" attribute of a parameter
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @return Current value of the "value" attribute of this parameter */
    const char* GetValueStringParameterPlugin(int indexParameter);
    
    /** Set a new value for an attribute of a return (only applied to "type, description" attributes)
     @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
     @param[in] nameAttribute Name of this attribute
     @param[in] newValue The new value set to this attribute */
    void SetAttributeReturnPlugin(int indexReturn, char nameAttribute[], char newValue[]);
    
    /** Get the current value of an attribute of a return (only applied to "type, description" attributes)
     @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
     @param[in] nameAttribute Name of this attribute
     @return Current value of this attribute */
    const char* GetAttributeReturnPlugin(int indexReturn, char nameAttribute[]);
    
    /** Set a new value (type "decimal") for the "value" attribute of a return
     @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
     @param[in] newValue The new value set to this attribute */
    void SetValueFloatReturnPlugin(int indexReturn, float newValue);
    
    /** Set a new value (type "integer") for the "value" attribute of a return
     @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
     @param[in] newValue The new value set to this attribute */
    void SetValueIntegerReturnPlugin(int indexReturn, int newValue);
    
    /** Set a new value (type "boolean") for the "value" attribute of a return
     @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
     @param[in] newValue The new value set to this attribute */
    void SetValueBooleanReturnPlugin(int indexReturn, bool newValue);
    
    /** Get the current value (type "decimal") of the "value" attribute of a return
     @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
     @return Current value of the "value" attribute of this return */
    float GetValueFloatReturnPlugin(int indexReturn);
    
    /** Get the current value (type "integer") of the "value" attribute of a return
     @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
     @return Current value of the "value" attribute of this return */
    int GetValueIntegerReturnPlugin(int indexReturn);
    
    /** Get the current value (type "boolean") of the "value" attribute of a return
     @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
     @return Current value of the "value" attribute of this return */
    bool GetValueBooleanReturnPlugin(int indexReturn);
    
    /** Save the namespace of the local applicatioin in a XML file
     @param[in] filePath Path leading to this file */
    void SaveToXMLPlugin(char filePath[]);
    
    /** Unregister the parameter data at an address in the local application
     @param[in] paramaterAddress Address of this parameter in the local application
     @param[in] indexParameter Index of this parameter in the vector of parameters (indexParameter = 0, 1, 2,...)
     @return 0: Cannot unregister the parameter data at this address
     @return 1: Unregister successfully the parameter data at this address */
    int UnregisterParameterDataPlugin(char paramaterAddress[], int indexParameter);
    
    /** Unregister the return data at an address in the local application
     @param[in] returnAddress Address of this return in the local application
     @param[in] indexReturn Index of this return in the vector of returns (indexReturn = 0, 1, 2,...)
     @return 0: Cannot unregister the return data at this address
     @return 1: Unregister successfully the return data at this address */
    int UnregisterReturnDataPlugin(char returnAddress[], int indexReturn);

    /** Unregister the message data at an address in the local application
     @param[in] messageAddress Address of this message in the local application
     @return 0: Cannot unregister the message data at this address
     @return 1: Unregister successfully the message data at this address */
    int UnregisterMessageDataPlugin(char messageAddress[]);
    
    /** Release the Minuit protocol */
    void ReleaseMinuitProtocolPlugin();
    
    /** Release the local and distant applications
     @param[in] localAppName Name of the local application
     @param[in] distantAppName Name of the distant application */
    void ReleaseApplicationsPlugin(char localAppName[], char distantAppName[]);
}

#endif
