#include "stdafx.h"
#include <list>
#include "BonusParser.h"
#include "Item.h"
#include "Player.h"
#include "Calc.h"
#include "Conifg.h"
#include "CWFile.h"
#include "CWString.h"
using namespace std;


CWUtils::CFile g_csv;


VOID WriteToCsv( CPlayer * aPlayer )
{
    EQUIP_TYPE nEquipType = aPlayer->GetEquipment(ITEM_MAIN_WEAPON)->GetEquipType();
    CCalc * pCalc = NULL;

    switch ( nEquipType )
    {
        case EQUIP_EMPTY :
        case EQUIP_KNUCKLE :
        case EQUIP_ONE_HAND_SWORD :
        case EQUIP_TWO_HAND_SWORD :
        case EQUIP_DUAL_SWORD :
        case EQUIP_BOW :
        {
            pCalc = new CBowCalc( aPlayer );
            break;
        }
        case EQUIP_BOWGUN :
        {
            pCalc = new CBowgunCalc( aPlayer );
            break;
        }
        case EQUIP_ROD :
        case EQUIP_MAGICAL_DEVICE :
        case EQUIP_HALBERD :
        {
            pCalc = new CBowCalc( aPlayer );
            break;
        }

        default :
        {
            wprintf_s( L"This weapon type is invalid. EquipType=%d\n" , nEquipType );
            break;
        }
    }

    
    string strLine , strTmp;
    if ( pCalc != NULL )
    {
        CWUtils::FormatStringA( strTmp , "%hs,%d,%d,%d,%d,%d,%d," , aPlayer->GetName() , 
                                aPlayer->GetProperty(PLAYER_STR) , aPlayer->GetProperty(PLAYER_DEX) , aPlayer->GetProperty(PLAYER_INT) , 
                                aPlayer->GetProperty(PLAYER_AGI) , aPlayer->GetProperty(PLAYER_VIT) , aPlayer->GetProperty(PLAYER_CRT) );
        strLine = strTmp;
        CWUtils::FormatStringA( strTmp , "%hs,%hs,%hs,%hs,%hs," , aPlayer->GetEquipment(ITEM_MAIN_WEAPON) ->ToString().c_str() ,
                                aPlayer->GetEquipment(ITEM_SUB_WEAPON) ->ToString().c_str() , aPlayer->GetEquipment(ITEM_ARMOR) ->ToString().c_str() ,
                                aPlayer->GetEquipment(ITEM_ADDITIONAL_EQUIPMENT) ->ToString().c_str() , aPlayer->GetEquipment(ITEM_SPECIAL_EQUIPMENT) ->ToString().c_str() );
        strLine += strTmp;

        CWUtils::FormatStringA( strTmp , "%d,%d,%d," , pCalc->GetMaxHp() , pCalc->GetMaxMp() , pCalc->GetAtkMpRecover() );
        strLine += strTmp;
        CWUtils::FormatStringA( strTmp , "%d,%d,%d," , pCalc->GetFinalCrt() , pCalc->GetFinalCrtDmg() , pCalc->GetFinalStability() );
        strLine += strTmp;
        CWUtils::FormatStringA( strTmp , "%d,%d,%d," , pCalc->GetFinalAtk() , pCalc->GetFinalCrtAtk() , pCalc->GetFinalAvgAtk() );
        strLine += strTmp;
        CWUtils::FormatStringA( strTmp , "%d,%d,%d," , pCalc->GetMainSkillAtk() , pCalc->GetMainSkillCrtAtk() , pCalc->GetMainSkillAvgAtk() );
        strLine += strTmp;
        CWUtils::FormatStringA( strTmp , "%d,%d,%d" , pCalc->GetMainSkillElementAtk() , pCalc->GetMainSkillCrtElementAtk() , pCalc->GetMainSkillAvgElementAtk() );
        strLine += strTmp;
        strLine += "\n";
    }

    g_csv.Write( (CONST UCHAR *)strLine.c_str() , strLine.length() );
}


VOID ForEachWeapon( CPlayer * aPlayer );
VOID ForEachArmor( CPlayer * aPlayer );
VOID ForEachAdditionalEquip( CPlayer * aPlayer );
VOID ForEachSpecialEquip( CPlayer * aPlayer );

VOID ForEachWeapon( CPlayer * aPlayer )
{
    for ( size_t uMainWeapon = 0 ; uMainWeapon < g_vecMainWeapons.size() ; uMainWeapon++ )
    {
        aPlayer->SetEquipment( g_vecMainWeapons[uMainWeapon] );
        for ( size_t uMainWeaponXtal1 = 0 ; uMainWeaponXtal1 < g_vecWeaponXtals.size() ; uMainWeaponXtal1++ )
        {
            g_vecMainWeapons[uMainWeapon]->SetXtal( 0 , g_vecWeaponXtals[uMainWeaponXtal1] );
            for ( size_t uMainWeaponXtal2 = uMainWeaponXtal1 + 1 ; uMainWeaponXtal2 < g_vecWeaponXtals.size() ; uMainWeaponXtal2++ )
            {
                g_vecMainWeapons[uMainWeapon]->SetXtal( 1 , g_vecWeaponXtals[uMainWeaponXtal2] );

                for ( size_t uSubWeapon = 0 ; uSubWeapon < g_vecSubWeapons.size(); uSubWeapon++ )
                {
                    aPlayer->SetEquipment( g_vecSubWeapons[uSubWeapon] );
                    ForEachArmor( aPlayer );
                }
            }
        }

        //Handle the case of no crystal
        g_vecMainWeapons[uMainWeapon]->SetXtal( 0 , NULL );
        g_vecMainWeapons[uMainWeapon]->SetXtal( 1 , NULL );
        for ( size_t uSubWeapon = 0 ; uSubWeapon < g_vecSubWeapons.size(); uSubWeapon++ )
        {
            aPlayer->SetEquipment( g_vecSubWeapons[uSubWeapon] );
            ForEachArmor( aPlayer );
        }
    }
}

VOID ForEachArmor( CPlayer * aPlayer )
{
    for ( size_t uArmor = 0 ; uArmor < g_vecArmors.size() ; uArmor++ )
    {
        aPlayer->SetEquipment( g_vecArmors[uArmor] );
        for ( size_t uArmorXtal1 = 0 ; uArmorXtal1 < g_vecArmorXtals.size() ; uArmorXtal1++ )
        {
            g_vecArmors[uArmor]->SetXtal( 0 , g_vecArmorXtals[uArmorXtal1] );
            for ( size_t uArmorXtal2 = uArmorXtal1 + 1 ; uArmorXtal2 < g_vecArmorXtals.size() ; uArmorXtal2++ )
            {
                g_vecArmors[uArmor]->SetXtal( 1 , g_vecArmorXtals[uArmorXtal2] );
                ForEachAdditionalEquip( aPlayer );
            }
        }

        //Handle the case of no crystal
        g_vecArmors[uArmor]->SetXtal( 0 , NULL );
        g_vecArmors[uArmor]->SetXtal( 1 , NULL );
        ForEachAdditionalEquip( aPlayer );
    }
}

VOID ForEachAdditionalEquip( CPlayer * aPlayer )
{
    for ( size_t uAdditionalEquip = 0 ; uAdditionalEquip < g_vecAdditionalEquips.size() ; uAdditionalEquip++ )
    {
        aPlayer->SetEquipment( g_vecAdditionalEquips[uAdditionalEquip] );
        for ( size_t uAdditionalEquipXtal1 = 0 ; uAdditionalEquipXtal1 < g_vecAdditionalXtals.size() ; uAdditionalEquipXtal1++ )
        {
            g_vecAdditionalEquips[uAdditionalEquip]->SetXtal( 0 , g_vecAdditionalXtals[uAdditionalEquipXtal1] );
            for ( size_t uAdditionalEquipXtal2 = uAdditionalEquipXtal1 + 1 ; uAdditionalEquipXtal2 < g_vecAdditionalXtals.size() ; uAdditionalEquipXtal2++ )
            {
                g_vecAdditionalEquips[uAdditionalEquip]->SetXtal( 1 , g_vecAdditionalXtals[uAdditionalEquipXtal2] );
                ForEachSpecialEquip( aPlayer );
            }
        }

        //Handle the case of no crystal
        g_vecAdditionalEquips[uAdditionalEquip]->SetXtal( 0 , NULL );
        g_vecAdditionalEquips[uAdditionalEquip]->SetXtal( 1 , NULL );
        ForEachSpecialEquip( aPlayer );
    }
}

VOID ForEachSpecialEquip( CPlayer * aPlayer )
{
    for ( size_t uSpecialEquip = 0 ; uSpecialEquip < g_vecSpecialEquips.size() ; uSpecialEquip++ )
    {
        aPlayer->SetEquipment( g_vecSpecialEquips[uSpecialEquip] );
        for ( size_t uSpecialEquipXtal1 = 0 ; uSpecialEquipXtal1 < g_vecSpecialXtals.size() ; uSpecialEquipXtal1++ )
        {
            g_vecSpecialEquips[uSpecialEquip]->SetXtal( 0 , g_vecSpecialXtals[uSpecialEquipXtal1] );
            for ( size_t uSpecialEquipXtal2 = uSpecialEquipXtal1 + 1 ; uSpecialEquipXtal2 < g_vecSpecialXtals.size() ; uSpecialEquipXtal2++ )
            {
                g_vecSpecialEquips[uSpecialEquip]->SetXtal( 1 , g_vecSpecialXtals[uSpecialEquipXtal2] );
                WriteToCsv( aPlayer );
            }
        }

        //Handle the case of no crystal
        g_vecSpecialEquips[uSpecialEquip]->SetXtal( 0 , NULL );
        g_vecSpecialEquips[uSpecialEquip]->SetXtal( 1 , NULL );
        WriteToCsv( aPlayer );
    }
}

INT wmain( INT aArgc , WCHAR * aArgv[] )
{
    UNREFERENCED_PARAMETER( aArgc );
    UNREFERENCED_PARAMETER( aArgv );
    _wsetlocale( LC_ALL , L".ACP" );
    wprintf_s( L"Start\n" );

    


    LoadDefaultConfig();




    //Open CSV file to write result
    g_csv.Open( L"Output.csv" , CWUtils::FILE_OPEN_ATTR_CREATE_ALWAYS , TRUE , TRUE , TRUE );

    string strLine;
    /*strLine.append( "Player,STR,DEX,INT,AGI,VIT,CRT,"
                    "MainWeapon,SubWeapon,Armor,AdditionalEquip,SpecialEquip,"
                    "MaxHp,MaxMp,AtkMpRecover,"
                    "FinalCrt,FinaltCrtDmg,FinalStability,"
                    "FinalAtk,FinalCrtAtk,FinalAvgAtk,"
                    "MainSkillAtk,MainSkillCrtAtk,MainSkillAvgAtk,"
                    "MainSkillElementAtk,MainSkillCrtElementAtk,MainSkillAvgElementAtk\n");*/
    strLine.append( "Player,STR,DEX,INT,AGI,VIT,CRT,"
                    "¥DªZ¾¹,°ÆªZ¾¹,¦çªA,°l¥[¸Ë³Æ,¯S®í¸Ë³Æ,"
                    "HP,MP,§ðÀ»¦^´_,"
                    "¼É²v,¼É¶Ë­¿²v%,Ã­©w«×,"
                    "ATK,ATK¼ÉÀ»,ATK¥­§¡¶Ë®`,"
                    "®zª®,®zª®¼ÉÀ»,®zª®¥­§¡¶Ë®`,"
                    "®zª®¹ïÄÝ,®zª®¹ïÄÝ¼ÉÀ»,®zª®¹ïÄÝ¥­§¡¶Ë®`\n");
    g_csv.Write( (CONST UCHAR *)strLine.c_str() , strLine.length() );

    for ( size_t uPlayer = 0 ; uPlayer < g_vecPlayers.size(); uPlayer++ )
    {
        CPlayer * player = g_vecPlayers[uPlayer];
        ForEachWeapon( player );
        //player->Reset( FALSE );
    }

    g_csv.Close();
    

    wprintf_s( L"End of the program\n" );
    system( "pause" );
    return 0;
}

