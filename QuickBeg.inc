| QuickBeg.inc - Version 4.4 - 09/15/2010 
| Written by MacQ with additions/suggestions by A_Druid_00, Niles, and Kroak
| 
| Copyright 2005-2010 by MacQ all rights reserved. 
| 
| This macro is only authorized for the personal use by members in good standing of the MacroQuest2 VIP forums 
| If you did not pay for VIP access, then you're a cheap, non contributing bastard who sucks the life out of 
| others and will die in hell. 
| 
|------------------------------------------------------------------------------------------------------------ 
| Release Notes: 
| 
| To integrate QuickBeg with your macro do the following: 
| - Add #include QuickBeg.inc to your Include section. 
| - Add /call QuickBegDeclares to your Declaration section. 
| - Add /call MeBegBuff, /call MeBegCure, /call MeBegItem, and /call PetBegBuff wherever you want to beg. 
| - Configure the INI file to meet your needs. 
| 
| The macro uses an INI file called QuickBeg.ini, and assums the INI file is stored in a sub folder called INI, 
| located in your macro folder. If you don't like the INI file being stored in a sub folder, then change the 
| variable qbIniFile below to a new path/name. 
| 
| The INI file is divided into a [GeneralSettings] section and a [CLASS/CHARNAME] section where [CLASS/CHARNAME] 
| is either your character name or your character class depending on how you set the variable groupIniByClass 
| in the [GeneralSettings] section. 
| 
| To utilize cure begging, this macro requires the MQ2Debuffs plugin from PinkFloyd33.  If you don't know how 
| to install/use plugins and/or can't located this plugin, then simply disable cure begging by setting MeBegCure 
| in the INI file to FALSE. 
| 
| ----- INI File Variables - [GeneralSettings] Section ----- 
| 
| - ForceAliasBuild = TRUE/FALSE controls the writing of aliases to your Macroquest.ini file.  If you don't 
|   want to worry about when you need to update your QuickBeg aliases in your Macroquest.ini file, then 
|   leave this set to TRUE.  However, if startup performance is important, then set this to FALSE but remember 
|   to set this to TRUE if/when you change/add aliases in/to your INI file or you get a new Macroquest.ini file. 
|   It is YOUR responsbility to mange this properly and keep YOUR aliases organized, you have been warned. 
| 
| - GroupIniByClass = TRUE/FALSE if this is set to TRUE, then the INI file will be devided into sections by 
|   class type.  If this is set to FALSE, then the INI file will be devided into sections by character name. 
| 
| - SearchRadius = Maximum radius QuickBeg will search for a buffer. 
| 
| - SearchZRadius = Maximum zradius QuickBeg will search for a buffer. 
| 
| - StatusMessages = RUE/FALSE reports QuickBeg settings each time you start.
|
| - MeBuffStacksDuration = The duration (ticks) before the buff will wear off you.  This allows you to ask for a
|   buff a number of ticks before it expires.
|
| - PetBuffStacksDuration = The duration (ticks) before the buff will wear off your pet.  This allows you to ask
|   for a pet buff a number of ticks before it expires.
| 
|   NOTE: the XX in the variable descriptions below are replaced by a "pseudo array" number (e.g., MeBegBuffName1, 
|   MeBegBuffName2, MeBegBuffName3, etc.) XX should never be a number larger than the appropriate variables 
|   that contain the totals for that particular group of variables (e.g., MeBegBuffTotal, MeBegCureTotal, 
|   MeBegItemTotal, and PetBegBuffTotal). 
| 
| - MeBegBuffTotal = Total number of Buffs QuickBeg could beg. Must be equal to the total number of Buffs in 
|   the MeBegBuff group listed in your INI file. 
| 
| - MeBegBuffNameXX = Contains the Name of the buff you want to beg.  QuickBeg will not beg for this buff if 
|   you are already wearing it or if this buff will NOT stack with another buff you are currently wearing. 
| 
| - MeBegBuffSourceXX = Contains the Class(s) (in three-letter class codes) that can cast the Buff listed in 
|   MeBegBuffNameXX or a substitute Buff from another class that is similar in nature to the Buff listed. List 
|   the Primary Class FIRST and any alternate classes after.  If you set AlternateBeg to TRUE, QuickBeg will look 
|   for alternate (substitute) classes if no Primary class is available.  Seperate each class with a verticle 
|   bar "|", do not start or end with a vertical bar. 
| 
| - MeBegBuffAliasXX = Contains the aliases for Buff(s) you want to beg for YOURSELF.  From inside EQ an alias 
|   controls on/off the begging for this buff. 
| 
| - MeBegBuffLevelXX = QuickBeg will not ask for this particular Buff if the PC is below this level. If you set the 
|   variable MinBegLevel to a number greater than zero, described below, it will superseed MeBegBuffLevelXX. 
| 
| - MeBegCureTotal = Total number of Cures QuickBeg could beg. Must be equal to the total number of Cures in 
|   the MeBegCure group listed in your INI file. 
| 
| - MeBegCureTypeXX = Contains the Type Name of the Curse you received.  This is per the different types of curses 
|   as part of the MQ2Debuffs plugin written by PinkFloyd33.  You will need to reference that plugin to determin 
|   the current types of debuff detection possible. 
| 
| - MeBegCureSourceXX = Contains the Class(s) (in three-letter class codes) that can cast a Cure for the curses 
|   listed in MeBegCureTypeXX or a substitute Cure from another class that is similar in nature to the Cure listed. 
|   List the Primary Class FIRST and any alternate classes after.  If you set AlternateBeg to TRUE, QuickBeg will look 
|   for alternate (substitute) classes if no Primary class is available.  Seperate each class with a verticle 
|   bar "|", do not start or end with a vertical bar. 
| 
| - MeBegCureAliasXX = These variables contain the aliases for Cure you want to beg for YOURSELF.  From inside EQ 
|   an alias controls on/off the begging for this cure. 
| 
| - MeBegCureLevelXX = QuickBeg will not ask for this particular Cure if the PC is below this level. If you set the 
|   variable MinBegLevel to a number greater than zero, described below, it will superseed MeBegCureLevelXX. 
| 
| - MeBegItemTotal = Total number of Items QuickBeg could beg. Must be equal to the total number of Items in 
|   the MeBegItem group listed in your INI file. 
| 
| - MeBegItemNameXX = Contains the Name(s) of the Item(s) you want to beg.  QuickBeg will not beg for this Item if 
|   you already have it in your inventory or on your cursor.  Seperate each item with a verticle bar '|', do not start 
|   or end with a verticle bar. 
| 
| - MeBegItemSourceXX = Contains the Class(s) (in three-letter class codes) that can cast this Item listed in 
|   MeBegItemNameXX or a substitute Item from another class that is similar in nature to the Item listed. 
|   List the Primary Class FIRST and any alternate classes after.  If you set AlternateBeg to TRUE, QuickBeg will look 
|   for alternate (substitute) classes if no Primary class is available.  Seperate each class with a verticle 
|   bar "|", do not start or end with a vertical bar. 
| 
| - MeBegItemAliasXX = Contains the aliases for Item(s) you want to beg for YOURSELF.  From inside EQ an alias controls 
|   (on/off) for begging this item. 
| 
| - MeBegItemLevelXX = QuickBeg will not ask for this particular Item if the PC is below this level. If you set the 
|   variable MinBegLevel to a number greater than zero, described below, it will superseed MeBegItemLevelXX. 
| 
| - PetBegBuffTotal = Total number of Pet Buffs QuickBeg could beg. Must be equal to the total number of Pet Buffs in 
|   the petBegBuff group listed in your INI file. 
| 
| - PetBegBuffNameXX = Contains the Name of the Buff you want to beg for YOUR PET.  QuickBeg will not beg for this 
|   buff if your pet is already wearing it or if this buff will not stack with another buff your pet is currently wearing. 
| 
| - PetBegBuffSourceXX = Contains the Class(s) (in three-letter class codes) that can cast the Pet Buff listed in 
|   PetBegBuffNameXX or a substitute Pet Buff from another class that is similar in nature to the Pet Buff listed. List 
|   the Primary Class FIRST and any alternate classes after.  If you set AlternateBeg to TRUE, QuickBeg will look 
|   for alternate (substitute) classes if no Primary class is available.  Seperate each class with a verticle 
|   bar "|", do not start or end with a vertical bar. 
| 
| - PetBegBuffAliasXX = Contains the aliases for Buff(s) you want to beg for YOUR PET.  From inside EQ an alias controls 
|   (on/off) begging for this pet buff. 
| 
| - PetBegBuffLevelXX = QuickBeg will not ask for this particular Pet Buff if the PC is below this level. If you set the 
|   variable MinBegLevel to a number greater than zero, described below, it will superseed PetBegBuffLevelXX.
| 
|   ----- Variables in INI - [CLASS/NAME] Section ----- 
| 
| - AllowAltBeg = TRUE/FALSE if you defined more than one class in meBegBuffSourceXX, meBegCureSourceXX, meBegItemSourceXX, 
|   or petBegBuffSourceXX, then if QuickBeg can't find the Primary Source (e.g., the FIRST CLASS LISTED) QuickBeg will look 
|   for other class sources you listed (Alternate Sources). For example, you first would probably look for a Magician to 
|   cast a damage shield but not finding one, you might look for a Druid; so you would list MAG|DRU.  Alias is /allowaltbeg 
| 
| - AskAnyone = TRUE/FALSE if set TRUE will ask anyone for buffs regardless if they are in your raid, group, or 
|   guild.  If you set this variable FALSE, QuickBeg will only check first for a raid member in range, 
|   then a group member in range, then a guild member in range. Alias is /askanyone 
| 
| - AskDelay = int variable containing the delay (in DECI-SECONDS) between sending the same buff request. This also 
|   means if you asked for a buff, received the buff then its dispelled or you click it off, QuickBeg will still 
|   wait the time specified in askDelay before asking again.  Alias is /askdelay 
| 
| - BegChannel = channel you will beg for buffs (e.g., tell, say, group, etc.) Six valid choices are: tell,t,i msg,g,say,i say 
|   Alias is /begchannel. 
| 
| - BegIfInvis = TRUE/FALSE will or will not beg if you are invised. Alias is /begifinvis. 
| 
| - MeBegBuff = TRUE/FALSE master on/off for personal buff begging.  Alias is /mebegbuff. 
| 
| - MeBegCure = TRUE/FALSE master on/off for personal cure begging. Alias is /mebegcure. 
| 
| - MeBegItem = TRUE/FALSE master on/off for personal item begging. Alias is /mebegitem. 
| 
| - PetBegBuff = TRUE/FALSE master on/off for pet buff begging. Alias is /petbegbuff. 
| 
| - MinBegLevel = If this variable is set to a positive number, you will not ask for buffs from anyone below this 
|   level.  However, if this variable is set to zero, QuickBeg will use individual spell specific level 
|   checks (e.g., MeBegBuffLevelXX, MeBegCureLevelXX, MeBegItemLevelXX, PetBegBuffLevelXX). Alias is /minbeglvl. 
| 
| - MeBegBuffStatusXX = TRUE/FALSE flag controlling Buff begging for the each personal buff. 
| 
| - MeBegBuffMessageXX = The message you want to send when you ask for this Buff. 
| 
| - MeBegCureStatusXX = TRUE/FALSE flag controlling Cure begging for the each debuff type. 
| 
| - MeBegCureMessageXX = The message you want to send when you ask for this Cure. 
| 
| - MeBegItemStatusXX = TRUE/FALSE flag controlling begging for an Item (like a mod rod) not in your inventory or 
|   on your cursor.  If QuickBeg finds the item in your inventory or on your cursor, it will NOT beg for it. 
| 
| - MeBegItemMessageXX = The message you want to send when you ask for this Item. 
| 
| - PetBegBuffStatusXX = TRUE/FALSE flag controlling Pet Buff begging for the buff. 
| 
| - PetBegBuffPetssageXX = The message you want to send when you ask for this Pet Buff. 
| 
| You can change several settings while the macro is running by typing an alias.  To use an alias, from an EQ command 
| line, type /XXX YYY (assuming there is an alias) where XXX is the alias name and YYY is the new value.  You don't 
| need to put quotes around the XXX value even if it has spaces. 
| 
| Example: 
| /askdelay 900 -- sets a the ask delay to 90 seconds. 
| /chatchannel i msg -- sets chat channel to "i msg". 
| 
| For changing Boolean variables you have a few choices.  You can type an alias, if you defined one in the INI file, 
| not followed by a new parameter and QuickBeg will simply toggle off (FALSE) if its ON, or ON (TRUE) if its OFF. You 
| can also pass a variety of parameters: 1, 0, TRUE, FALSE, ON, or OFF. 
| 
| Example- Assuming you defined an alias called /begsow, which in this example might control begging for Spirit of 
| the Wolf, here are your options: 
| /begsow on -- turns Oak begging on. 
| /begsow off --  turns Oak begging off. 
| /begsow TRUE -- turns Oak begging on. 
| /begsow FALSE -- turns Oak begging off. 
| /begsow -- turns OFF if its currently ON, or turns ON if its currently OFF (toggle style). 
|------------------------------------------------------------------------------------------------------------ 
| 
#event QBSetVar "[MQ2] QBSetVar:#*#" 

Sub QuickBegDeclares 
   /declare MeBegBuffCounter     int      outer 1 
   /declare MeBegCureCounter     int      outer 1 
   /declare MeBegItemCounter     int      outer 1 
   /declare PetBegBuffCounter    int      outer 1 
   /declare SpamDelayTimer       timer    outer 
   /declare QbIniFile            string   outer ./QuickBeg.ini 
   /declare i                    int      local 

   /call QBDeclareIniVar ForceAliasBuild  bool     GeneralSettings TRUE 
   /if ( ${ForceAliasBuild} ) { 
      /echo QuickBeg writing aliases to your Macroquest.ini file. 
      /echo You can disbale this by setting forceAliasBuild to FALSE in your ${QbIniFile} file. 
   } 

   /call QBDeclareIniVar GroupIniByClass        bool    GeneralSettings FALSE 
   /call QBDeclareIniVar PetNameSuffix          bool    GeneralSettings TRUE 
   /call QBDeclareIniVar SearchRadius           int     GeneralSettings 100 
   /call QBDeclareIniVar SearchZRadius          int     GeneralSettings 100 
   /call QBDeclareIniVar StatusMessages         bool    GeneralSettings FALSE
   /call QBDeclareIniVar MeBuffStacksDuration   int     GeneralSettings 0 
   /call QBDeclareIniVar PetBuffStacksDuration  int     GeneralSettings 0 

   /call QBDeclareIniVar AllowAltBeg      bool     ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE /allowaltbeg 
   /call QBDeclareIniVar AskDelay         int      ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} 1800  /askdelay 
   /call QBDeclareIniVar AskAnyone        bool     ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE /askanyone 
   /call QBDeclareIniVar BegChannel       string   ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} tell  /begchannel 
   /call QBDeclareIniVar BegIfInvis       bool     ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE /begifinvis 
   /call QBDeclareIniVar MeBegBuff        bool     ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE /mebegbuff 
   /call QBDeclareIniVar MeBegItem        bool     ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE /mebegitem 
   /call QBDeclareIniVar MeBegCure        bool     ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE /mebegcure 
   /call QBDeclareIniVar PetBegBuff       bool     ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE /petbegbuff 
   /call QBDeclareIniVar MinBegLevel      int      ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} 0     /minbeglevel 

   /call QBDeclareIniVar MeBegBuffTotal               int      GeneralSettings 1 
   /if ( ${MeBegBuffTotal} ) { 
      /for i 1 to ${MeBegBuffTotal} 
         /declare MeBegBuffTimer${i}                  timer  outer 
         /call QBDeclareIniVar MeBegBuffName${i}      string GeneralSettings "REPLACE WITH SINGLE BUFF NAME" 
         /call QBDeclareIniVar MeBegBuffSource${i}    string GeneralSettings "REPLACE WITH BUFFING PC CLASS(S) SEPERATED BY VERTICLE BAR '|' IF MORE THAN ONE CLASS" 
         /if ( ${MinBegLevel} ) { 
            /declare MeBegBuffLevel${i}               int outer ${MinBegLevel} 
         } else { 
            /call QBDeclareIniVar MeBegBuffLevel${i}  int    GeneralSettings 
         } 
         /call QBDeclareIniVar MeBegBuffStatus${i}    bool   ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE 
         /call QBDeclareIniVar MeBegBuffMessage${i}   string ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} "REPLACE WITH BEG BUFF MESSAGE" 
         /if ( ${ForceAliasBuild} ) /call QBAliasIniVar MeBegBuffAlias${i} GeneralSettings MeBegBuffStatus${i} 
      /next i 
   } 

   /call QBDeclareIniVar MeBegCureTotal               int    GeneralSettings 1 
   /if ( ${MeBegCureTotal} ) { 
      /for i 1 to ${MeBegCureTotal} 
         /declare MeBegCureTimer${i}                  timer  outer 
         /call QBDeclareIniVar MeBegCureType${i}      string GeneralSettings "REPLACE WITH SINGLE CURSE NAME (per MQ2Debuffs plugin)" 
         /call QBDeclareIniVar MeBegCureSource${i}    string GeneralSettings "REPLACE WITH CURING PC CLASS(S) SEPERATED BY VERTICLE BAR '|' IF MORE THAN ONE CLASS" 
         /if ( ${MinBegLevel} ) { 
            /declare MeBegCureLevel${i}               int outer ${MinBegLevel} 
         } else { 
            /call QBDeclareIniVar MeBegCureLevel${i}  int GeneralSettings 
         } 
         /call QBDeclareIniVar MeBegCureStatus${i}    bool ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE
         /call QBDeclareIniVar MeBegCureMessage${i}   string ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} "REPLACE WITH BEG CURE MESSAGE" 
         /if ( ${ForceAliasBuild} ) /call QBAliasIniVar MeBegCureAlias${i} GeneralSettings MeBegCureStatus${i} 
      /next i 
   } 

   /call QBDeclareIniVar MeBegItemTotal               int      GeneralSettings 1 
   /if ( ${MeBegItemTotal} ) { 
      /for i 1 to ${MeBegItemTotal} 
         /declare MeBegItemTimer${i}                  timer outer 
         /call QBDeclareIniVar MeBegItemName${i}      string GeneralSettings "REPLACE WITH ITEM NAMES(S) SEPERATED BY VERTICLE BAR '|' IF MORE THAN ONE ITEM" 
         /call QBDeclareIniVar MeBegItemSource${i}    string GeneralSettings "REPLACE WITH SUMMONING PC CLASS(S) SEPERATED BY VERTICLE BAR '|' IF MORE THAN ONE CLASS" 
         /if ( ${MinBegLevel} ) { 
            /declare MeBegItemLevel${i}               int outer ${MinBegLevel} 
         } else { 
            /call QBDeclareIniVar MeBegItemLevel${i}  int    GeneralSettings 
         } 
         /call QBDeclareIniVar MeBegItemStatus${i}    bool   ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE 
         /call QBDeclareIniVar MeBegItemMessage${i}   string ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} "REPLACE WITH BEG ITEM MESSAGE" 
         /if ( ${ForceAliasBuild} ) /call QBAliasIniVar MeBegItemAlias${i} GeneralSettings MeBegItemStatus${i} 
      /next i 
   } 

   /call QBDeclareIniVar PetBegBuffTotal              int      GeneralSettings 1 
   /if ( ${PetBegBuffTotal} ) { 
      /for i 1 to ${PetBegBuffTotal} 
         /declare PetBegBuffTimer${i}                 timer outer 
         /call QBDeclareIniVar PetBegBuffName${i}     string GeneralSettings "REPLACE WITH SINGLE PET BUFF NAME" 
         /call QBDeclareIniVar PetBegBuffSource${i}   string GeneralSettingS "REPLACE WITH BUFFING PC CLASS(S) SEPERATED BY VERTICLE BAR '|' IF MORE THAN ONE CLASS" 
         /if ( ${MinBegLevel} ) { 
            /declare PetBegBuffLevel${i}              int outer ${MinBegLevel} 
         } else { 
            /call QBDeclareIniVar PetBegBuffLevel${i} int    GeneralSettings 
         } 
         /call QBDeclareIniVar PetBegBuffStatus${i}   bool   ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} FALSE 
         /call QBDeclareIniVar PetBegBuffMessage${i}  string ${If[${GroupIniByClass},${Me.Class.ShortName},${Me.CleanName}]} "REPLACE WITH PET BEG BUFF MESSAGE" 
         /if ( ${ForceAliasBuild} ) /call QBAliasIniVar PetBegBuffAlias${i} GeneralSettings PetBegBuffStatus${i} 
      /next i 
   } 

   /if ( ${StatusMessages} ) { 
      /if ( !${MeBegBuff} ) { 
         /echo QuickBeg will NOT beg for My Buffs. 
      } else { 
         /echo QuickBeg will beg for My Buffs. 
      } 
      /if ( !${MeBegCure} ) { 
         /echo QuickBeg will NOT beg for My Cures. 
      } else { 
         /echo QuickBeg will beg for My Cures. 
      } 
      /if ( !${MeBegItem} ) { 
         /echo QuickBeg will NOT beg for My Items. 
      } else { 
         /echo QuickBeg will beg for My Items. 
      } 
      /if ( !${PetBegBuff} ) { 
         /echo QuickBeg will NOT beg for Pet Buffs. 
      } else { 
         /echo QuickBeg will beg for Pet Buffs. 
      } 
      /if ( ${MeBegBuff} || ${MeBegCure} || ${MeBegItem} || ${PetBegBuff} ) { 
         /if ( ${AskAnyone} ) { 
            /echo QuickBeg will beg from anyone in Range. 
         } else { 
               /echo QuickBeg will only beg from Raid/Group/Guild members in Range. 
         } 
         /if ( ${AllowAltBeg} ) { 
            /echo QuickBeg will beg from Alternate sources. 
         } else { 
            /echo QuickBeg will NOT beg from Alternate sources. 
         } 
         /echo QuickBeg will wait ${Int[${Math.Calc[${AskDelay}/10]}]} seconds between requests for the same buff. 
         /echo QuickBeg will beg in channel: /${BegChannel} 
         /if ( ${BegIfMeInvis} ) { 
            /echo QuickBeg will beg for buffs if I am invised. 
         } else { 
            /echo QuickBeg will NOT beg for buffs if I am invised. 
         } 
      } 
   } 
/return 

Sub MeBegBuff 
   /if ( ${SpamDelayTimer} || !${MeBegBuffTotal} || !${MeBegBuff} || !${Me.FreeBuffSlots} || ( ${Me.Invis} && !${BegIfInvis} ) ) /return 
   /declare i int local 
   /declare j int local 
   /for i ${MeBegBuffCounter} to ${MeBegBuffTotal} 
      /if ( ${MeBegBuffStatus${i}} && !${MeBegBuffTimer${i}} && ${Spell[${MeBegBuffName${i}}].Stacks[${MeBuffStacksDuration}]} ) { 
         /for j 1 to ${Math.Calc[${MeBegBuffSource${i}.Count[|]}+1]} 
            /call FindBuffer "${MeBegBuffMessage${i}}" ${MeBegBuffSource${i}.Arg[${j},|]} MeBegBuffTimer${i} ${MeBegBuffLevel${i}} 
            /if ( ${Macro.Return.Equal[BEG_SUCCESS]} ) { 
               /call IncrementCounter "MeBegBuffCounter" "MeBegBuffTotal" 
               /return 
            } 
         /if ( ${AllowAltBeg} ) /next j 
      } 
   /call IncrementCounter "MeBegBuffCounter" "MeBegBuffTotal" 
   /next i 
/return 

Sub MeBegCure 
   /if ( ${SpamDelayTimer} || !${MeBegCureTotal} || !${MeBegCure} || ( ${Me.Invis} && !${BegIfInvis} ) ) /return 
   /declare i int local 
   /declare j int local 
   /for i ${MeBegCureCounter} to ${MeBegCureTotal} 
      /if ( ${MeBegCureStatus${i}} && !${MeBegCureTimer${i}} && ${Debuff.${MeBegCureType${i}}} ) { 
         /for j 1 to ${Math.Calc[${MeBegCureSource${i}.Count[|]}+1]} 
            /call FindBuffer "${MeBegCureMessage${i}}" ${MeBegCureSource${i}.Arg[${j},|]} MeBegCureTimer${i} ${MeBegCureLevel${i}} 
            /if ( ${Macro.Return.Equal[BEG_SUCCESS]} ) { 
               /call IncrementCounter "MeBegCureCounter" "MeBegCureTotal" 
               /return 
            } 
         /if ( ${AllowAltBeg} ) /next j 
      } 
   /call IncrementCounter "MeBegCureCounter" "MeBegCureTotal" 
   /next i 
/return 

Sub MeBegItem 
   /if ( ${SpamDelayTimer} || !${MeBegItemTotal} || !${MeBegItem} || ( ${Me.Invis} && !${BegIfInvis} ) ) /return 
   /declare i int local 
   /declare j int local 
   /for i ${MeBegItemCounter} to ${MeBegItemTotal} 
      /for j 1 to ${Math.Calc[${MeBegItemSource${i}.Count[|]}+1]} 
         /if ( ${MeBegItemStatus${i}} && !${MeBegItemTimer${i}} && !${FindItem[${MeBegItemName${i}.Arg[${j},|]}].ID} && !${Cursor.Name.Equal[${MeBegItemName${i}.Arg[${j},|]}]} ) { 
            /call FindBuffer "${MeBegItemMessage${i}}" ${MeBegItemSource${i}.Arg[${j},|]} MeBegItemTimer${i} ${MeBegItemLevel${i}} 
            /if ( ${Macro.Return.Equal[BEG_SUCCESS]} ) { 
               /call IncrementCounter "MeBegItemCounter" "MeBegItemTotal" 
               /return 
            } 
         } 
      /if ( ${AllowAltBeg} ) /next j 
      /call IncrementCounter "MeBegItemCounter" "MeBegItemTotal" 
   /next i 
/return 

Sub PetBegBuff 
   /if ( ${SpamDelayTimer} || !${Me.Pet.ID} || !${PetBegBuffTotal} || !${PetBegBuff} || ( ${Me.Invis} && !${BegIfInvis} ) ) /return 
   /declare i int local 
   /declare j int local 
   /for i ${PetBegBuffCounter} to ${PetBegBuffTotal} 
      /if (${PetBegBuffStatus${i}} && !${PetBegBuffTimer${i}} && ${Spell[${PetBegBuffName${i}}].StacksPet[${PetBuffStacksDuration}]} ) { 
         /for j 1 to ${Math.Calc[${PetBegBuffSource${i}.Count[|]}+1]} 
            /call FindBuffer "${PetBegBuffMessage${i}} ${Me.Pet.CleanName}" ${PetBegBuffSource${i}.Arg[${j},|]} PetBegBuffTimer${i} 
            /if (${Macro.Return.Equal[BEG_SUCCESS]}) { 
               /call IncrementCounter "PetBegBuffCounter" "PetBegBuffTotal" 
               /return 
            } 
         /if ( ${AllowAltBeg} ) /next j 
      } 
   /call IncrementCounter "PetBegBuffCounter" "PetBegBuffTotal" 
   /next i 
/return 

Sub FindBuffer(string BegBuff, string BegClass, string BegTimer, int MinBufferLevel) 
   /if ( ${Me.Class.ShortName.Equal[${BegClass}]} )  /return BEG_SUCCESS 
   /if ( ${NearestSpawn[pc group ${BegClass} range ${MinBufferLevel} 100 radius ${SearchRadius} zradius ${SearchZRadius}].ID} ) /call BegForBuff "${BegBuff}" ${NearestSpawn[PC group ${BegClass} range ${MinBufferLevel} 100]} ${BegTimer} 
   /if ( ${Macro.Return.NotEqual[BEG_SUCCESS]} && ${NearestSpawn[pc raid ${BegClass} range ${MinBufferLevel} 100 radius ${SearchRadius} zradius ${SearchZRadius}].ID} ) /call BegForBuff "${BegBuff}" ${NearestSpawn[PC raid ${BegClass} range ${MinBufferLevel} 100]} ${BegTimer} 
   /if ( ${Macro.Return.NotEqual[BEG_SUCCESS]} && ${NearestSpawn[pc guild ${BegClass} range ${MinBufferLevel} 100 radius ${SearchRadius} zradius ${SearchZRadius}].ID} && ${Me.Guild.NotEqual[NULL]} ) /call BegForBuff "${BegBuff}" ${NearestSpawn[PC guild ${BegClass} range ${MinBufferLevel} 100]} ${BegTimer} 
   /if ( ${Macro.Return.NotEqual[BEG_SUCCESS]} && ${AskAnyone} && ${NearestSpawn[pc ${BegClass} range ${MinBufferLevel} 100 radius ${SearchRadius} zradius ${SearchZRadius}].ID} ) /call BegForBuff "${BegBuff}" ${NearestSpawn[PC ${BegClass} range ${MinBufferLevel} 100]} ${BegTimer} 
/return ${Macro.Return} 

Sub BegForBuff(string BegBuff, string BufferName, sring BegTimer) 
   /if ( ${BegChannel.Equal[tell]} || ${BegChannel.Equal[t]} || ${BegChannel.Equal[i msg]} || ${BegChannel.Equal[bct]} ) { 
      /docommand /${BegChannel} ${BufferName} ${BegBuff} 
      /varset ${BegTimer} ${AskDelay} 
      /varset SpamDelayTimer 3s 
      /return BEG_SUCCESS 
   } else { 
      /if ( ${BegChannel.Equal[g]} || ${BegChannel.Equal[say]} || ${BegChannel.Equal[i say]} || ${BegChannel.Equal[bc]} ) { 
      /docommand /${BegChannel} ${BegBuff} 
      /varset ${BegTimer} ${AskDelay} 
      /varset SpamDelayTimer 3s 
      /return BEG_SUCCESS 
   } 
/return BEG_FAILED 

Sub IncrementCounter(string BegVarCounterName, string BegVarTotalName) 
   /if ( ${${BegVarCounterName}}==${${BegVarTotalName}} ) { 
      /varset ${BegVarCounterName} 1 
   } else { 
      /varcalc ${BegVarCounterName} ${${BegVarCounterName}}+1 
   } 
/return 

Sub QBDeclareIniVar(string VarName, string VarType, string SectionName, string VarValue, string Alias) 
   /if ( !${Defined[${VarName}]} ) /declare ${VarName} ${VarType} outer 
   /declare TempString string local ${Ini[${QbIniFile},${SectionName},${VarName},NOTFOUND]} 
   /if ( ${TempString.Equal[NOTFOUND]} ) { 
      /varset ${VarName} ${VarValue} 
      /ini "${QbIniFile}" "${SectionName}" "${VarName}" "${${VarName}}" 
   } else { 
      /varset ${VarName} ${TempString} 
   } 
   /if ( ${ForceAliasBuild} && ${Defined[alias]} ) /squelch /alias ${Alias} /echo QBSetVar: ${VarName} 
   } 
/return 

Sub QBAliasIniVar(string VarName, string SectionName, string AliasVar) 
   /declare TempString string local ${Ini[${QbIniFile},${SectionName},${VarName},NOTFOUND]} 
   /if ( ${TempString.NotEqual[NOTFOUND]} && ${ForceAliasBuild} ) /squelch /alias ${TempString} /echo QBSetVar: ${AliasVar} 
/return 

Sub Event_QBSetVar(string Line) 
   /declare VarName  string local ${Line.Arg[3]} 
   /declare NewValue string local ${Line.Arg[4]} 
   /if ( !${Defined[${VarName}]} ) /return 
   /if ( ${${VarName}(type).Name.Equal[bool]} && ${NewValue.Equal[NULL]} ) { 
      /if ( ${${VarName}} ) { 
         /varset ${VarName} FALSE 
         /echo ${VarName} is now OFF 
      } else { 
         /varset ${VarName} TRUE 
         /echo ${VarName} is now ON 
      } 
   } else { 
      /if ( ${${VarName}(type).Name.Equal[bool]} ) { 
         /if ( ${NewValue.Equal[on]} || ${NewValue.Equal[1]} || ${NewValue.Equal[true]} ) { 
         /varset ${VarName} TRUE 
         } else { 
            /if ( ${NewValue.Equal[off]} || ${NewValue.Equal[0]} || ${NewValue.Equal[false]} ) { 
            /varset ${VarName} FALSE 
            } else { 
               /echo ${VarName} was NOT changed 
            } 
         } 
      } else { 
         /if ( !${NewValue.Equal[NULL]} ) { 
            /varset ${VarName} ${NewValue} 
            /echo ${VarName} is now ${${VarName}} 
         } else { 
            /echo ${VarName} was NOT changed 
         } 
      } 
   } 
   /if ( ${GroupIniByClass} ) { 
      /ini "${QbIniFile}" "${Me.Class.ShortName}" "${VarName}" "${${VarName}}" 
   } else { 
      /ini "${QbIniFile}" "${Me.CleanName}" "${VarName}" "${${VarName}}" 
   } 
/return
