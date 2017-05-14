#include "stdafx.h"
#include "Conifg.h"
using namespace std;


vector<CPlayer *> g_vecPlayers;
vector<CEquipment *> g_vecMainWeapons , g_vecSubWeapons , g_vecArmors , g_vecAdditionalEquips , g_vecSpecialEquips;
vector<CXtal *> g_vecGeneralXtals , g_vecWeaponXtals , g_vecArmorXtals , g_vecAdditionalXtals , g_vecSpecialXtals;

typedef struct _ItemProperty
{
    string strName;
    string strBonus;
} ItemProperty;

BOOL LoadDefaultConfig()
{
    //Players
    CPlayer * player = new CPlayer();
    player->SetProperty( PLAYER_LV , 125 );
    player->SetProperty( PLAYER_DEX , 255 );
    player->SetProperty( PLAYER_STR , 87 );
    g_vecPlayers.push_back( player );
   
    player = new CPlayer();
    player->SetProperty( PLAYER_LV , 125 );
    player->SetProperty( PLAYER_DEX , 255 );
    player->SetProperty( PLAYER_STR , 19 );
    player->SetProperty( PLAYER_CRT , 68 );
    g_vecPlayers.push_back( player );
    
    player = new CPlayer();
    player->SetProperty( PLAYER_LV , 125 );
    player->SetProperty( PLAYER_DEX , 255 );
    player->SetProperty( PLAYER_CRT , 87 );
    g_vecPlayers.push_back( player );



    string aryMainWeapons[] = { "ATK7% Cd5% Cd12 C12" /*, "ATK7% Cd5% Cd11 C11"*/ , "ATK7% D5% Cd12 C12" /*, "ATK7% D5% Cd11 C11"*/ /*, "ElementAtk11% ATK7% C11" , "ATK7% D7% C11" , "ATK7% D6% C11% C11" *//*, "ATK7% Cd5% C11% C11"*/ };
    ItemProperty arySubWeapons[] = { /*{ "¹ïÄÝ½b" , "Atk20 ElementAtk25%" } ,*/
                                     { "¤b¥Ú" , "Atk22 C3 Cd1 Stability-2%" } ,
                                     { "±M®aªº½b" , "Atk30 Stability2%" } };
    string aryArmors[] = { /*"D3% Cd7% Cd12 C12" ,*/ "D5% Cd7% Cd12 C12" , "D5% Cd7% Cd-2 C12 A1% MA1%" /*, "D7% Cd5% Cd12 C12"*/ /*, "ATK7% DEX7% C11"*/ /*, "D7% Cd7% C11% C11" , "D7% Cd11 C11% C11"*/ };
    ItemProperty aryAdditionalEquips[] = { { "­ô¼wÂ§´U" , "C15" } ,
                                           /*{ "§l¦å°­¤æÁO" , "Atk1% Stability5% Avoid2" } ,*/
                                           /*{ "¿ß§À¤Ú" , "Stability3% Agi3% Dex3% Hit15% Avoid15%" } ,*/
                                           /*{ "¥¨Às¨¤" , "Atk4% Stability2%" } ,*/
                                           { "»l¦±¨¤" , "Matk4% Stability8%" }
                                           /*{ "ÀsÀY²¯" , "WeaponAtk10 C10" }*/ /*,
                                           { "·tÃM©Ü­·" , "ATK2% Cd2% ShortRangeAtk2%" }*/ };
    ItemProperty arySpecialEquips[] = { { "§ÞÅ@Å@²ÅIII" , "D6 MP400" } ,
                                        { "¤pÅ]´¹¦Q¹¢" , "Atk1% Matk1% MP300" } };

    ItemProperty aryGeneralXtals [] = { { "ª÷ÄÝ¨ëÃÈ" , "A2% Cd3 MSPD-1%" } ,
                                        { "¼ÉÀ»²v+3" , "C3" } };
    ItemProperty aryWeaponXtals[] = { { "¥Û¬WÅ]¹³" , "MP300 ShortRangeAtk3% PowerResistBreaker3%" } ,
                                      { "¥Ì·ç¤Ò" , "A3% D2% ASPD1%" } ,
                                      { "¾®ºA¾Ô±N" , "A5% AtkMpRecover2" } };
    ItemProperty aryArmorXtals[] = { /*{ "æy¤ú¤ý" , "HP1000 WeaponAtk1%" } ,*/
                                     { "«Ê¦LÃ~" , "HP1000 Cd1" } ,
                                     { "»B»A³¾" , "MP300 AtkMpRecover1 CSPD100" } };
    ItemProperty aryAdditionalXtals[] = { { "¨g¼ÉÀs" , "Cd2 C6" } };
    ItemProperty arySpecialXtals[] = { { "Å]´¹¯¥¤â" , "WeaponAtk10% C5 Hit15% MP-100" } /*,
                                       { "°{ÆF²Ô¤h" , "A1% MA1% Cd1% AtkMpRecover3" }*/ };
    //Load main weapons
    for ( size_t i = 0 ; i < _countof(aryMainWeapons) ; i++ )
    {
        CEquipment * item = new CEquipment( ITEM_MAIN_WEAPON , EQUIP_BOWGUN );
        item->ParseBonus( aryMainWeapons[i] );
        INT nAtk = 100 , nRefineLv = 15 , nStability = 60;
        BOOL bHasElementAtkRate = ( item->GetBonusValue( BONUS_ELEMENT_ATK_RATE ) > 0 ) ? TRUE : FALSE;
        switch ( item->GetEquipType() )
        {
            case EQUIP_BOW :
            {
                nAtk = 60;
                nRefineLv = ( bHasElementAtkRate ) ? 12 : 15;
                nStability = 60;
                break;
            }
            case EQUIP_BOWGUN :
            {
                nAtk = 80;
                nRefineLv = ( bHasElementAtkRate ) ? 12 : 15;
                nStability = 50;
                break;
            }
            default :
            {
                wprintf_s( L"Unhandled equipment type. EquipType=%d\n" , item->GetEquipType() );
                break;
            }
        }
        item->SetProperty( nAtk , nRefineLv , nStability );
        g_vecMainWeapons.push_back( item );
    }
    //Load sub-weapons
    for ( size_t i = 0 ; i < _countof(arySubWeapons) ; i++ )
    {
        CEquipment * item = new CEquipment( ITEM_SUB_WEAPON , EQUIP_ARROW );
        item->SetName( arySubWeapons[i].strName );
        item->SetProperty( 10 , 0 , 20 );
        item->ParseBonus( arySubWeapons[i].strBonus );
        g_vecSubWeapons.push_back( item );
    }
    //Load armors
    for ( size_t i = 0 ; i < _countof(aryArmors) ; i++ )
    {
        CEquipment * item = new CEquipment( ITEM_ARMOR , EQUIP_ARMOR );
        item->SetProperty( 50 , 13 , 0 );
        item->ParseBonus( aryArmors[i] );
        g_vecArmors.push_back( item );
    }
    //Load additional equipments
    for ( size_t i = 0 ; i < _countof(aryAdditionalEquips) ; i++ )
    {
        CEquipment * item = new CEquipment( ITEM_ADDITIONAL_EQUIPMENT , EQUIP_ADDITIONAL_EQUIPMENT );
        item->SetName( aryAdditionalEquips[i].strName );
        item->SetProperty( 15 , 13 , 0 );
        item->ParseBonus( aryAdditionalEquips[i].strBonus );
        g_vecAdditionalEquips.push_back( item );
    }
    //Load special equipments
    for ( size_t i = 0 ; i < _countof(arySpecialEquips) ; i++ )
    {
        CEquipment * item = new CEquipment( ITEM_SPECIAL_EQUIPMENT , EQUIP_SPECIAL_EQUIPMENT );
        item->SetName( arySpecialEquips[i].strName );
        item->SetProperty( 6 , 0 , 0 );
        item->ParseBonus( arySpecialEquips[i].strBonus );
        g_vecSpecialEquips.push_back( item );
    }

    //Load crystals
    //Generate a general dummy crystal to calculate the case of no crystal
    CXtal * pDummyGeneralXtal = new CXtal( ITEM_GENERAL_XTAL );
    for ( size_t i = 0 ; i < _countof(aryGeneralXtals) ; i++ )
    {
        CXtal * item = new CXtal( ITEM_GENERAL_XTAL );
        item->SetName( aryGeneralXtals[i].strName );
        item->ParseBonus( aryGeneralXtals[i].strBonus );
        g_vecGeneralXtals.push_back( item );
    }
    g_vecGeneralXtals.push_back( pDummyGeneralXtal );

    for ( size_t i = 0 ; i < _countof(aryWeaponXtals) ; i++ )
    {
        CXtal * item = new CXtal( ITEM_WEAPON_XTAL );
        item->SetName( aryWeaponXtals[i].strName );
        item->ParseBonus( aryWeaponXtals[i].strBonus );
        g_vecWeaponXtals.push_back( item );
    }
    g_vecWeaponXtals.insert( g_vecWeaponXtals.end() , g_vecGeneralXtals.begin() , g_vecGeneralXtals.end() );

    for ( size_t i = 0 ; i < _countof(aryArmorXtals) ; i++ )
    {
        CXtal * item = new CXtal( ITEM_ARMOR_XTAL );
        item->SetName( aryArmorXtals[i].strName );
        item->ParseBonus( aryArmorXtals[i].strBonus );
        g_vecArmorXtals.push_back( item );
    }
    g_vecArmorXtals.insert( g_vecArmorXtals.end() , g_vecGeneralXtals.begin() , g_vecGeneralXtals.end() );

    for ( size_t i = 0 ; i < _countof(aryAdditionalXtals) ; i++ )
    {
        CXtal * item = new CXtal( ITEM_ADDITIONAL_EQUIPMENT_XTAL );
        item->SetName( aryAdditionalXtals[i].strName );
        item->ParseBonus( aryAdditionalXtals[i].strBonus );
        g_vecAdditionalXtals.push_back( item );
    }
    g_vecAdditionalXtals.insert( g_vecAdditionalXtals.end() , g_vecGeneralXtals.begin() , g_vecGeneralXtals.end() );

    for ( size_t i = 0 ; i < _countof(arySpecialXtals) ; i++ )
    {
        CXtal * item = new CXtal( ITEM_SPECIAL_EQUIPMENT_XTAL );
        item->SetName( arySpecialXtals[i].strName );
        item->ParseBonus( arySpecialXtals[i].strBonus );
        g_vecSpecialXtals.push_back( item );
    }
    g_vecSpecialXtals.insert( g_vecSpecialXtals.end() , g_vecGeneralXtals.begin() , g_vecGeneralXtals.end() );

    return TRUE;
}