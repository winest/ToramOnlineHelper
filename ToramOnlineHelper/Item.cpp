#include "stdafx.h"
#include "Item.h"
using namespace std;

std::map< ITEM_TYPE , std::string> g_mapItemTypeName;
BOOL GetItemNameByType( ITEM_TYPE aItemType , std::string & aOutput )
{
    BOOL bRet = FALSE;
    if ( g_mapItemTypeName.size() == 0 )
    {
        g_mapItemTypeName[ITEM_MAIN_WEAPON] = "MainWeapon";
        g_mapItemTypeName[ITEM_SUB_WEAPON] = "SubWeapon";
        g_mapItemTypeName[ITEM_ARMOR] = "Armor";
        g_mapItemTypeName[ITEM_ADDITIONAL_EQUIPMENT] = "AdditionEquip";
        g_mapItemTypeName[ITEM_SPECIAL_EQUIPMENT] = "SpecialEquip";
        g_mapItemTypeName[ITEM_GENERAL_XTAL] = "GeneralXtal";
        g_mapItemTypeName[ITEM_WEAPON_XTAL] = "WeaponXtal";
        g_mapItemTypeName[ITEM_ARMOR_XTAL] = "ArmorXtal";
        g_mapItemTypeName[ITEM_ADDITIONAL_EQUIPMENT_XTAL] = "AdditionalEquipXtal";
        g_mapItemTypeName[ITEM_SPECIAL_EQUIPMENT_XTAL] = "SpecialEquipXtal";
    }

    auto it = g_mapItemTypeName.find( aItemType );
    if ( it != g_mapItemTypeName.end() )
    {
        aOutput = it->second;
        bRet = TRUE;
    }
    return bRet;
}



ITEM_TYPE CItem::GetItemType()
{
    return m_nItemType;
}

VOID CItem::SetName( std::string aName )
{
    m_strName = aName;
}

CONST CHAR * CItem::GetName()
{
    return m_strName.c_str();
}

BOOL CItem::ParseBonus( std::string aProp )
{
    return CBonusParser::GetInstasnce()->Parse( aProp , m_mapBonus );
}

INT CItem::GetBonusValue( BONUS_TYPE aBonusType )
{
    return m_mapBonus[aBonusType];  //For equipment, it's value without Xtals
}

std::string CItem::ToString()
{
    string strRet , strTmp;
    if ( m_strName.length() > 0 )
    {
        strRet = m_strName;
    }
    if ( GetItemNameByType( m_nItemType , strTmp ) )
    {
        strRet += string( "(" ) + strTmp + string( ") " );
    }
    CBonusParser::GetInstasnce()->GetBonusDisplayString( m_mapBonus , strTmp );
    strRet.append( strTmp );

    return strRet;
}




std::string CXtal::ToString()
{
    return m_strName;
}









std::map< EQUIP_TYPE , std::string> g_mapEquipTypeName;
BOOL GetEquipNameByType( EQUIP_TYPE aEquipType , std::string & aOutput )
{
    BOOL bRet = FALSE;
    if ( g_mapEquipTypeName.size() == 0 )
    {
        g_mapEquipTypeName[EQUIP_EMPTY] = "Empty";
        g_mapEquipTypeName[EQUIP_KNUCKLE] = "Knuckle";
        g_mapEquipTypeName[EQUIP_ONE_HAND_SWORD] = "OHS";
        g_mapEquipTypeName[EQUIP_TWO_HAND_SWORD] = "THS";
        g_mapEquipTypeName[EQUIP_DUAL_SWORD] = "DualSword";
        g_mapEquipTypeName[EQUIP_BOW] = "Bow";
        g_mapEquipTypeName[EQUIP_BOWGUN] = "Bowgun";
        g_mapEquipTypeName[EQUIP_ROD] = "Rod";
        g_mapEquipTypeName[EQUIP_MAGICAL_DEVICE] = "MD";
        g_mapEquipTypeName[EQUIP_HALBERD] = "Halberd";
        g_mapEquipTypeName[EQUIP_ARROW] = "Arrow";
        g_mapEquipTypeName[EQUIP_SHIELD] = "Shield";
        g_mapEquipTypeName[EQUIP_KNIFE] = "Knife";
        g_mapEquipTypeName[EQUIP_ARMOR] = "Armor";
        g_mapEquipTypeName[EQUIP_ADDITIONAL_EQUIPMENT] = "AdditionalEquip";
        g_mapEquipTypeName[EQUIP_SPECIAL_EQUIPMENT] = "SpecialEquip";
    }

    auto it = g_mapEquipTypeName.find( aEquipType );
    if ( it != g_mapEquipTypeName.end() )
    {
        aOutput = it->second;
        bRet = TRUE;
    }
    return bRet;
}



EQUIP_TYPE CEquipment::GetEquipType()
{
    return m_nEquipType;
}

BOOL CEquipment::SetProperty( INT aAtkOraDef , INT aRefineLv , INT aStability )
{
    m_nAtkOrDef = aAtkOraDef;
    m_nRefineLv = min( max ( 0 , aRefineLv ) , 15 );
    m_nStability = aStability;
    return TRUE;
}

BOOL CEquipment::GetProperty( INT & aAtkOraDef , INT & aRefineLv , INT & aStability )
{
    aAtkOraDef = m_nAtkOrDef;
    aRefineLv = m_nRefineLv;
    aStability = m_nStability;
    return TRUE;
}

BOOL CEquipment::SetXtal( INT aSlotIndex , CXtal * aXtal )
{
    _ASSERT( 0 <= aSlotIndex && aSlotIndex < EQUIP_MAX_SLOT_CNT );
    BOOL bRet = FALSE;
    do 
    {
        if ( aXtal == NULL )
        {
            bRet = TRUE;
            break;
        }

        if ( aXtal->GetItemType() == ITEM_GENERAL_XTAL )
        {
            bRet = TRUE;
            break;
        }

        switch ( m_nItemType )
        {
            case ITEM_MAIN_WEAPON :
            case ITEM_SUB_WEAPON :
            {
                if ( aXtal->GetItemType() == ITEM_WEAPON_XTAL )
                {
                    bRet = TRUE;
                }
                break;
            }

            case ITEM_ARMOR :
            {
                if ( aXtal->GetItemType() == ITEM_ARMOR_XTAL )
                {
                    bRet = TRUE;
                }
                break;
            }

            case ITEM_ADDITIONAL_EQUIPMENT :
            {
                if ( aXtal->GetItemType() == ITEM_ADDITIONAL_EQUIPMENT_XTAL )
                {
                    bRet = TRUE;
                }
                break;
            }

            case ITEM_SPECIAL_EQUIPMENT :
            {
                if ( aXtal->GetItemType() == ITEM_SPECIAL_EQUIPMENT_XTAL )
                {
                    bRet = TRUE;
                }
                break;
            }

            default :
            {
                wprintf_s( L"This item type cannot have Xtal. ItemType=%d\n" , m_nItemType );
                break;
            }
        }
    } while ( 0 );

    if ( bRet == TRUE )
    {
        m_pXtals[aSlotIndex] = aXtal;
    }
    return bRet;
}

CXtal * CEquipment::GetXtal( INT aSlotIndex )
{
    _ASSERT( 0 <= aSlotIndex && aSlotIndex < EQUIP_MAX_SLOT_CNT );
    return m_pXtals[aSlotIndex];
}


std::string CEquipment::ToString()
{
    string strRet , strTmp;
    if ( m_strName.length() > 0 )
    {
        strRet = m_strName;
    }
    else 
    {
        if ( ( m_nItemType == ITEM_MAIN_WEAPON || m_nItemType == ITEM_SUB_WEAPON ) &&
             ( GetEquipNameByType( m_nEquipType , strTmp ) ) )
        {
            strRet = strTmp;
        }
    }
    
    if ( m_nItemType == ITEM_MAIN_WEAPON )
    {
        CHAR szAtk[32] = {};
        sprintf_s( szAtk , "%d" , m_nAtkOrDef );
        strRet.append( szAtk );

        if ( m_nRefineLv > 1 )
        {
            CHAR * szRefine[] = { "+0" , "+1" , "+2" , "+3" , "+4" , "+5" , "+6" , "+7" ,
                                  "+8" , "+9" , "+E" , "+D" , "+C" , "+B" , "+A" , "+S" };
            strRet.append( szRefine[m_nRefineLv] );
        }
    }


    if ( m_nItemType == ITEM_MAIN_WEAPON || m_nItemType == ITEM_SUB_WEAPON || m_nItemType == ITEM_ARMOR )
    {
        CBonusParser::GetInstasnce()->GetBonusDisplayString( m_mapBonus , strTmp );
        if ( strRet.length() > 0 )
        {
            strRet.append( " " );
        }
        strRet.append( strTmp );
    }

    if ( m_pXtals[0] != NULL )
    {
        if ( strRet.length() > 0 )
        {
            strRet.append( " " );
        }
        strRet.append( m_pXtals[0]->ToString() );
    }

    if ( m_pXtals[1] != NULL )
    {
        if ( strRet.length() > 0 )
        {
            strRet.append( " " );
        }
        strRet.append( m_pXtals[1]->ToString() );
    }
    return strRet;
}