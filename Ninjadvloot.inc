| Ninjadvloot.inc v2.5  01/01/2013 Redguides.com 
| Author A_Druid_00 12/19/2005
| Based on original looting code of toomanynames
| The following updates were all individually posted and consolidated by Maskoi into the current version.
| Updated: Moeymoejoe added strip out comma in item names when accessing ini file 08/02/2006
| Updated: mystikule added sell option to ini file 01/07/2008
| Updated: drkrain for House of Thule 10/23/2010
| Updated: Maskoi with Sell Routines 11/27/2010
| Updated: Maskoi with /item keep/sell/destroy ini commands 07/21/2011
| Updated: Maskoi with Foraged item handling 08/31/2011
| Updated: Maskoi with Buying item handling 07/31/2012
| Updated: Maskoi with Assign different ini file for item handling 01/01/2013
|
| Selling Contributions by
|   drkrain - TLInv item check
|   dewey2461 - Add sold items to ini file Event
|
| Requirements: MQ2Moveutils
| Usage: add the following to your macro for looting
|   #include Ninjadvloot.inc
|   /call SetupAdvLootVars
|   /call LootMobs
|
| Assign differnent ini files. Default is Loot.ini
|   /call SetupAdvLootVars "MyToonLoot.ini"
|   /call SetupAdvLootVars "LootMesa.ini"
|
| Commands
| Usage. Grab the item and put it on your cursor then use one of the following commands
| /lootdestroy - Mark item on cursor to Destroy in Loot.ini file
| /lootignore - Mark item on cursor to Ignore in Loot.ini file
| /lootkeep - Mark item on cursor to Keep in Loot.ini file
| /lootsell - Mark item on cursor to Sell in Loot.ini file
| /sellstuff - Target a vendor and this command will sell any item in your inventory marked sell. 
| /depositstuff - Target your guildbanker and this command will deposit any item in your inventory marked keep into the guild bank.

#Event ALCantLoot       "#*#may not loot this corpse#*#"
#Event Sell             "#*#You receive#*# for the #1#(s)#*#"
#Event EditIniItem      "[MQ2] LootIniItem #1# #2#"
#Event SellStuff        "[MQ2] NinjadvLoot selling items to vendor"
#Event Broke            "#*#you cannot afford#*#" 
#Event Broke            "#*#you can't afford#*#" 
#Event Forage           "Your forage mastery has enabled you to find something else!"
#Event Forage           "You have scrounged up #*#"
#Event InventoryFull    "#*#Your inventory appears full!#*#"

Sub SetupAdvLootVars(string ChangeIniFile)

    /declare ALDontLoot                         int                 outer 
    /declare CorpseRotTimer                     timer               outer
    /declare NinjadVersion                      string              outer   2.5
    /declare InventoryFull                      int                 outer   0
    /declare NinjaIniFile                       string              outer   Loot.ini
    /if (${ChangeIniFile.Length}) {
        /varset NinjaIniFile ${ChangeIniFile}
        /echo Ninja Advance Loot in now writing all info to the ${ChangeIniFile} file.
    }
    /declare Version                            string              outer   ${Ini[${NinjaIniFile},Settings,Version]}
    /if (!${Ini[${NinjaIniFile},Settings,Version].Length}) {
        /call CreateIni
        /ini "${NinjaIniFile}" "Settings" "Version" "0.0"
    }
    /if (${Version.NotEqual[${NinjadVersion}]}) {
        /echo NinjAdvLoot version mismatch detected writing aliases.
        /noparse /squelch /alias /lootignore    /echo LootIniItem Ignore ${Cursor.Name}
        /noparse /squelch /alias /lootsell      /echo LootIniItem Sell ${Cursor.Name}
        /noparse /squelch /alias /lootkeep      /echo LootIniItem Keep ${Cursor.Name}
        /noparse /squelch /alias /lootdestroy   /echo LootIniItem Destroy ${Cursor.Name}
        /squelch /alias /sellstuff              /echo NinjadvLoot selling items to vendor
        /squelch /alias /depositstuff           /echo NinjadvLoot depositing items to guildbank
        /ini "${NinjaIniFile}" "Settings" "Version" "${NinjadVersion}"
    }

    | Loot ini settings
    /call ALLoadVar Settings OpenAllBags        1                   int
    /call ALLoadVar Settings AddNewSales        1                   int
    /call ALLoadVar Settings LootForage         1                   int
    /call ALLoadVar Settings LootMobs           TRUE                bool
    /call ALLoadVar Settings CorpseRadius       100                 int
    /call ALLoadVar Settings MobsTooClose       100                 int
    /call ALLoadVar Settings CorpseRotTime      440s                string
    /call ALLoadVar Settings ReportLoot         FALSE               bool
    /call ALLoadVar Settings LootChannel        g                   string
    /call ALLoadVar Settings LootForageSpam     1                   int
    | Alertlist 9 used to define an ignore list like campfires untargetable etc.
    /if (!${Defined[${AlertList}]}) /declare AlertList int outer 9
    | Alertlist 25 used to define corpses to ignore that were already looted.
    /squelch /alert clear 25
/return

Sub ALLoadVar(IniSection,IniVar,IniValue,VarType)

    /if (!${Defined[${IniVar}]} && ${Defined[VarType]}) /declare ${IniVar} ${VarType} outer
    /declare IniString string local ${Ini[${NinjaIniFile},${IniSection},${IniVar},NOTFOUND]}
    /varset ${IniVar} ${IniString}
    /if (${IniString.Equal["NOTFOUND"]}) {
        /if (${IniString.Equal["NOTFOUND"]}) /varset ${IniVar} ${IniValue}
        /ini "${NinjaIniFile}" "${IniSection}" "${IniVar}" "${${IniVar}}"
    } 

/return

| ****************  Loot Mobs Section ******************** |

Sub Event_ALCantLoot
   /varset ALDontLoot ${Target.ID}
/return

Sub LootMobs
    /squelch /alert add ${AlertList} untargetable
    /squelch /alert add ${AlertList} campfire
    /if (!${LootMobs} || ${SpawnCount[npc radius ${MobsTooClose} zradius 50 noalert ${AlertList}]} || !${SpawnCount[corpse radius ${CorpseRadius} zradius 50 noalert 25]} || ${Me.Combat} || (${Cursor.NoDrop} && !${Me.FreeInventory})) /return
    /if (!${CorpseRotTimer}) /squelch /alert clear 25
    /declare i int local
    /declare CorpseList string local |
    /declare ZDist float local ${Math.Distance[${Target.Z}:${Me.Z}]}
    /for i 1 to ${SpawnCount[corpse radius ${CorpseRadius} zradius 50 noalert 25]}
        /varset CorpseList ${CorpseList}${NearestSpawn[${i},corpse radius ${CorpseRadius} noalert 25].ID}|
    /next i
    /declare DeadCount int local ${SpawnCount[corpse radius ${CorpseRadius} zradius 50 noalert 25]}
    | /if (${Me.Mount.ID}) /dismount
    /for i 1 to ${DeadCount}
        /if (${Spawn[${CorpseList.Arg[${i},|]}].Deity.ID} && ${Spawn[${CorpseList.Arg[${i},|]}].ID}) /squelch /alert add 25 id ${Spawn[${CorpseList.Arg[${i},|]}].Deity.ID}
        /if (${Spawn[${CorpseList.Arg[${i},|]}].ID} && ${Spawn[${CorpseList.Arg[${i},|]}].LineOfSight} && !${Spawn[${CorpseList.Arg[${i},|]}].Deity.ID}) {
            /if (${Target.ID}!=${Spawn[${CorpseList.Arg[${i},|]}].ID}) /target id ${Spawn[${CorpseList.Arg[${i},|]}].ID}
            /if (!${Me.Standing}) /stand
            /delay 2s ${Target.ID}==${Spawn[${CorpseList.Arg[${i},|]}].ID} && ${Me.Standing}
            /if (${Spawn[${CorpseList.Arg[${i},|]}].Distance}>5) {
                /moveto mdist 10
                /moveto loc ${Spawn[${CorpseList.Arg[${i},|]}].Y} ${Spawn[${CorpseList.Arg[${i},|]}].X} 
                /delay 250 ${MoveTo.Stopped}
                /call ZCheck ${ZDist} 5
                /face fast
            }
            /delay 10s ${Spawn[${CorpseList.Arg[${i},|]}].Distance}<10
            /if (${Spawn[${CorpseList.Arg[${i},|]}].Distance}<10) /call LootCorpse
        }
    /next i
/return

Sub LootCorpse
    /declare i              int    local
    /declare LootList       string local
    /declare FirstLetter    string local
    /call CheckCursor
    /loot
    /delay 3s ${Corpse.Open}
    /doevents ALCantLoot
    /if (${Target.ID}==${ALDontLoot} && ${Spawn[${ALDontLoot}].ID}) /squelch /alert add 25 id ${ALDontLoot}
    /delay 3s ${Corpse.Items} || ${Target.ID}==${ALDontLoot}
    /if (${Corpse.Open} && ${Corpse.Items}) {
        /declare loottotal int  local
        :ALlootlag
        /varset loottotal ${Corpse.Items}
        /delay 1s ${loottotal}!=${Corpse.Items}
        /if (${loottotal}!=${Corpse.Items}) /goto :ALlootlag
        /for i 1 to ${loottotal}
            /varset FirstLetter ${Corpse.Item[${i}].Name.Left[1]}
            /if (${Corpse.Item[${i}].ID} && !${Select[${Ini[${NinjaIniFile},"${FirstLetter}","${Corpse.Item[${i}]}"]},Ignore,Keep,Destroy,Sell]}) {
                /if (${Corpse.Item[${i}].NoDrop}) /ini "${NinjaIniFile}" "${FirstLetter}" "${Corpse.Item[${i}]}" Ignore
                /if (!${Corpse.Item[${i}].NoDrop}) /ini "${NinjaIniFile}" "${FirstLetter}" "${Corpse.Item[${i}]}" Keep
            }    
            /if (${Ini[${NinjaIniFile},"${FirstLetter}","${Corpse.Item[${i}]}"].NotEqual[Destroy]} && !${Me.FreeInventory} && (!${FindItemCount[=${Corpse.Item[${i}].Name}]} || (${FindItemCount[=${Corpse.Item[${i}].Name}]} && ${Corpse.Item[${i}].Stackable} && !${Corpse.Item[${i}].FreeStack})) || (${Corpse.Item[${i}].Lore} && ${FindItem[${Corpse.Item[${i}]}].ID}) || ${Ini[${NinjaIniFile},"${FirstLetter}","${Corpse.Item[${i}]}"].Equal[Ignore]}) /varset LootList ${LootList}${Corpse.Item[${i}]},
            /if ((${Ini[${NinjaIniFile},"${FirstLetter}","${Corpse.Item[${i}]}"].Equal[Keep]} || ${Ini[${NinjaIniFile},"${FirstLetter}","${Corpse.Item[${i}]}"].Equal[Sell]}) && (!${Corpse.Item[${i}].Lore} || !${FindItem[${Corpse.Item[${i}]}].ID}) && (${Me.FreeInventory} || (${FindItemCount[=${Corpse.Item[${i}].Name}]} && ${Corpse.Item[${i}].Stackable} && ${Corpse.Item[${i}].FreeStack}))) /call LootItem ${i} Keep Right
            /if (${Ini[${NinjaIniFile},"${FirstLetter}","${Corpse.Item[${i}]}"].Equal[Destroy]}) /call LootItem ${i} Destroy left
        /next i
        /if (${Corpse.Items}) {
            /if (${ReportLoot} && ${LootList.Length}) {
                /keypress Enter 
                /keypress / chat
                /call Type "${LootChannel}"
                /keypress Space chat
                /notify LootWND LW_BroadcastButton leftmouseup 
                /delay 5
                /call Type " left on corpse."
                /keypress /
                /keypress Enter chat
            }
            /if (${Target.ID}) /squelch /alert add 25 id ${Target.ID}
            /varset CorpseRotTimer ${CorpseRotTime}
        }
    }
    :clickdoneffs
        /nomodkey /notify LootWnd LW_DoneButton leftmouseup
        /delay 5s !${Window[LootWnd].Open}
    /if (${Window[LootWnd].Open}) /goto :clickdoneffs
/return

Sub LootItem(int i,DoWhat,WhichButton)
    /declare CorpseItemID int local ${Corpse.Item[${i}].ID}
    /nomodkey /shift /itemnotify  ${Corpse.Item[${i}].InvSlot} ${WhichButton}mouseup
    /delay 5s ${Window[ConfirmationDialogBox].Open} || !${Corpse.Item[${i}].NoDrop}
    /if (${Window[ConfirmationDialogBox].Open}) /nomodkey /notify ConfirmationDialogBox Yes_Button leftmouseup
    /delay 5s ${Cursor.ID} || ${WhichButton.NotEqual[left]}
    /if (${DoWhat.Equal[Destroy]} && ${Cursor.ID}==${CorpseItemID}) /destroy
    /delay 3s !${Corpse.Item[${i}].ID}
    /if (${Cursor.ID}) /call CheckCursor
/return

Sub CheckCursor
    :ALauto_inv
        /if (${Cursor.ID}) {
            /if (${Cursor.NoDrop} && !${Me.FreeInventory}) /return
            /timed 5 /autoinventory
            /delay 2s !${Cursor.ID}
    /goto :ALauto_inv
    }
/return

| **************** Foraged Items Section ******************** |
Sub Event_Forage
    /if (!${LootForage}) /return
    /declare ForagedItem string local
    :MoreToAutoInventory
        /if (${Cursor.ID}) {
            /varset ForagedItem ${Cursor.Name}
            /if (!${Select[${Ini[${NinjaIniFile},"${Cursor.Name.Left[1]}","${Cursor.Name}"]},Ignore,Keep,Destroy,Sell]}) {
                /if (${Cursor.ID}) /ini "${NinjaIniFile}" "${Cursor.Name.Left[1]}" "${Cursor.Name}" Keep
                /if (${LootForageSpam}) /echo New foraged item >> ${Cursor.Name} << added to ini file. 
            }
            /if (${Ini[${NinjaIniFile},"${Cursor.Name.Left[1]}","${Cursor.Name}"].Equal[Destroy]} || ${Ini[${NinjaIniFile},"${Cursor.Name.Left[1]}","${Cursor.Name}"].Equal[Ignore]}) {
                /if (${Cursor.Name.Equal[${ForagedItem}]})     /destroy
                /delay 5
                /if (${LootForageSpam}) /echo NINJADVLOOT --  Destroyed foraged ${ForagedItem}.
            } else /if ((${Ini[${NinjaIniFile},"${Cursor.Name.Left[1]}","${Cursor.Name}"].Equal[Keep]} || ${Ini[${NinjaIniFile},"${Cursor.Name.Left[1]}","${Cursor.Name}"].Equal[Sell]}) && (!${Cursor.Lore} || !${FindItem[${Cursor.Name}].ID}) && (${Me.FreeInventory} || (${FindItemCount[=${Cursor.Name}]} && ${Cursor.Stackable} && ${Cursor.FreeStack}))) {
                /if (${LootForageSpam}) /echo NINJADVLOOT ++ Kept foraged ${ForagedItem}.
                /autoinventory
                /delay 5
            }
        }
    /if (${Cursor.ID}) /goto :MoreToAutoInventory
/return

| **************** Search Loot Section ******************** |
Sub DoLootStuff(LootAction)
    /declare i int local
    /declare j int local
    /declare k int local
    /declare LootItem string
    /if (${OpenAllBags}) {
        /echo Opening all bags
        /keypress OPEN_INV_BAGS
    }
   /call NPC "${Target.CleanName}"
   | Top level inv has its own loop since ${FindItem[=${ItemToSell}].InvSlot} looks at top lev inv slots first in Sub SellToVendor for the item to sell.
   | Loop through top level inventory slots for sellable items
   /for k 1 to 10
        | Check if top level inv slot is not a container/bag
        /if (${InvSlot[pack${k}].Item.Container}==0) {
            | If top level inv slot is empty check for an item marked sell
            /if (${InvSlot[pack${k}].Item.ID}) {
                /varset LootItem ${InvSlot[pack${k}].Item}
                /if (${LootAction.Equal[sell]})  {
                /if (${Ini[${NinjaIniFile},"${LootItem.Left[1]}","${LootItem}"].Equal[Sell]}) /call SellToVendor "${LootItem}"
                }
                /if (${LootAction.Equal[deposit]})  {
                    /if (${Ini[${NinjaIniFile},"${LootItem.Left[1]}","${LootItem}"].Equal[Keep]}) /call DepositToGuildBank "${LootItem}"
                }
            }
        }
    /next k      
    | Loop through top level inventory slots for containers
    /for i 1 to 10
        | Check if top level inv slot has a bag
        /if (${InvSlot[pack${i}].Item.Container}==0) /next i
        | Set j 1 to number of bag slots and loop through slots looking for items marked sell
        /for j 1 to ${InvSlot[pack${i}].Item.Container}
            /if (${InvSlot[pack${i}].Item.Item[${j}].ID}) {
            /varset LootItem ${InvSlot[pack${i}].Item.Item[${j}].Name}
            /if (${LootAction.Equal[sell]})  {
                /if (${Ini[${NinjaIniFile},"${LootItem.Left[1]}","${LootItem}"].Equal[Sell]}) /call SellToVendor "${LootItem}"
                }
                /if (${LootAction.Equal[deposit]})  {
                    /if (${Ini[${NinjaIniFile},"${LootItem.Left[1]}","${LootItem}"].Equal[Keep]}) /call DepositToGuildBank "${LootItem}"
                }
            }
        /next j
    /next i

    /if (${OpenAllBags}) {
        /echo Closing all bags
        /keypress CLOSE_INV_BAGS
    }
    | Prevent spam from Sell event after selling items in Sub SellStuff
    /doevents flush Sell
    /if (${Window[MerchantWnd].Open}) {
        /echo Closing merchant window
        /nomodkey /notify MerchantWnd MW_Done_Button LeftMouseUp
    }
    /if (${Window[GuildBankWnd].Open}) {
        /echo Closing guildbank window
        /keypress esc
    }
/return
   
Sub NPC(NPCName)
    /target npc ${NPCName}
    /delay 1s
    /if (!${Select[${Target.Type},npc,pet]} || !${Target.ID} || ${Target.Type.Equal[pet]} && !${Target.CleanName.Find[familiar]}) {
        /echo Please target a vendor or guildbanker
        /return
    }
    /echo Doing business with ${NPCName}
    /target id ${Spawn[${NPCName}].ID}
    /delay 3s ${Target.ID}==${Spawn[${NPCName}].ID}
    /if (${Target.Distance}>15) {
        /moveto id  ${Spawn[${NPCName}].ID}
        /delay 250 ${MoveTo.Stopped}
    }
    /face nolook
    /delay 1s
    /echo Opening merchant/guildbank window
    /nomodkey /click right target
    /echo Waiting 5s for merchant/guildbank window to populate
    /delay 5s
/return

| **************** Sell Loot Section ******************** |
Sub Event_Sell(string soldstr, string ItemName)
    /if ( ${AddNewSales} ) {
        /echo Setting ${ItemName} to sell
        /ini "${NinjaIniFile}" "${ItemName.Left[1]}" "${ItemName}" Sell
    }
/return

Sub SellToVendor(ItemToSell)
    /if (${Window[MerchantWnd].Open}) {
    :sell
        /echo Selling ${ItemToSell}
        /nomodkey /itemnotify ${FindItem[=${ItemToSell}].InvSlot} leftmouseup
        /delay 5
        /nomodkey /shiftkey /notify merchantwnd MW_Sell_Button leftmouseup
        /delay 2s
    /if (${FindItem[${itemToSell}].InvSlot}) /goto :sell
    }
/return

| **************** Deposit Loot Section ******************** 
Sub DepositToGuildBank(ItemToDeposit)
    /if (${Window[GuildBankWnd].Open}) {
        :deposit
            /if (${Window[GuildBankWnd].Child[GBANK_DepositCountLabel].Text.Arg[2,:]}==0) {
                /echo Guildbank Deposited Items is full.
                /return
            }
            /if (${FindItem[=${ItemToDeposit}].InvSlot}<=22) /return
            /echo Depositing ${ItemToDeposit}
            /nomodkey /shiftkey /itemnotify ${FindItem[=${ItemToDeposit}].InvSlot} leftmouseup
            /delay 5
            /nomodkey /notify GuildBankWnd GBANK_DepositButton leftmouseup
            /delay 2s
        /if (${FindItem[${itemToSell}].InvSlot}) /goto :deposit
    }
/return

| **************** Item set ini file event ******************** 
    Sub Event_EditIniItem(ItemString,ItemAction,ItemName)
        /if (${Cursor.ID}) {
            /echo -- Setting ${ItemName} to ${ItemAction}
            /ini "${NinjaIniFile}" ${ItemName.Left[1]} "${ItemName}" ${ItemAction}
        } else {
            /echo No item on cursor.
        }
    /return

| **************** Sell Stuff Event ******************** 
    Sub Event_SellStuff
        /call DoLootStuff sell
    /return
    
| **************** Deposit Stuff Event *******************
    Sub Event_DepositStuff
        /call DoLootStuff deposit
    /return
    
| **************** Broke Event ******************** 
Sub Event_Broke 
    /echo You are out of money! 
    /endmacro 
/return

| **************** Type Stuff  ******************** 
| Lifted from commonsubs.inc by Armysoldier    
    Sub Type(InStr) 
    /declare char string local 
    /declare loopctr int local 
    /for loopctr 1 to ${InStr.Length} 
        /varset char ${InStr.Mid[${loopctr},1]} 
        /if (!${char.Length}) { 
            /nomodkey /keypress space chat 
        } else { 
            /nomodkey /keypress ${char} chat 
        } 
    /next loopctr 
/return 

| **************** Buy Stuff ********************  
Sub Buy(string ItemToBuy, int amount)
    /declare i int local
    | /echo Buying ${ItemToBuy}!
    /declare QTY int local
    /declare ListItem int local
    /varcalc QTY ${amount}-${FindItemCount[${ItemToBuy}]}
    /delay 1s
    /if (${FindItemCount[${ItemToBuy}]}>= ${amount}) {
        /echo I have enough ${ItemToBuy}.
        /return
    }   
    /varset ListItem ${Window[MerchantWnd].Child[ItemList].List[=${ItemToBuy},2]}
    /if (!${ListItem}) {
        /echo couldn't find ${ItemToBuy}
        /return
    } else {
        /notify MerchantWnd ItemList listselect ${ListItem}
        /delay 1s       
    } 
    /echo Buying ${ItemToBuy} Till I get ${amount} 
    :Loop
    /doevents
    /if (${InventoryFull}) /return
    /if (${QTY}>1) {
        /if (${QTY}>19) {
            /Shiftkey /notify merchantwnd MW_Buy_Button leftmouseup
            /delay 2s ${FindItemCount[${ItemToBuy}]}>=${QTY}
            /echo ${FindItemCount[${ItemToBuy}]} ${ItemToBuy} in inventory
            /varcalc QTY ${amount}-${FindItemCount[${ItemToBuy}]} 
            /delay 3
            /if (${QTY}<=0) /return
            /goto :Loop
        }
        /if (${QTY}>0 && ${QTY}<20) {
            /for i 1 to ${QTY} 
                /ctrlkey /notify merchantwnd MW_Buy_Button leftmouseup
                /delay 2s ${FindItemCount[${ItemToBuy}]}>=${Math.Calc[${FindItemCount[${ItemToBuy}]}+${i}]}
                /echo Buying ${ItemToBuy} ${i} of ${QTY}
                /if (${i}>=${QTY}) {
                    /echo ${FindItemCount[${ItemToBuy}]} ${ItemToBuy} in inventory
                    /return
                }
            /next i
            /varcalc QTY ${amount}-${FindItemCount[${ItemToBuy}]}
            
        }
    }
/return
    
Sub ZCheck(float Zcur, float Zdiff)
    | Move down if Z distance more than Zcheck due to levitation
    /if (${Zcur}>=${Zdiff}) {
        /keypress end hold
        /delay 10
        /keypress end
    }
/return

Sub Event_InventoryFull
    /echo Your Inventory is full. Turning off looting functions.
    /varset LootMobs FALSE
    /varset InventoryFull 1
/return

Sub CreateIni
    /if (${Ini[${NinjaIniFile}].Length}) /return
    /declare a local Settings|A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z
    /echo Creating ini file ${NinjaIniFile}
    /declare i int local 1
    /for i 1 to 27
        /ini ${NinjaIniFile} "${a.Arg[${i},|]}" "|===================================" "==================================|"
    /next i
/return