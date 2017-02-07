#include "stdafx.h"
#include "Player.h"
using namespace std;

VOID CPlayer::Reset( BOOL aClearName )
{
    if ( aClearName )
    {
        m_strName.clear();
    }

    for ( INT i = 0 ; i < PLAYER_PROPERTY_COUNT ; i++ )
    {
        m_mapProps[(PLAYER_PROPERTY)i] = 1;
    }
    m_mapEquips.clear();
}


VOID CPlayer::SetName( std::string aName )
{
    m_strName = aName;
}
CONST CHAR * CPlayer::GetName()
{
    return m_strName.c_str();
}

BOOL CPlayer::SetProperty( PLAYER_PROPERTY aProp , INT aPropValue )
{
    BOOL bRet = FALSE;
    m_mapProps[aProp] = aPropValue;
    bRet = TRUE;
    return bRet;
}

INT CPlayer::GetProperty( PLAYER_PROPERTY aProp )
{
    INT nRet = 0;
    auto it = m_mapProps.find( aProp );
    if ( it != m_mapProps.end() )
    {
        nRet = it->second;
    }
    return nRet;
}

BOOL CPlayer::SetEquipment( CEquipment * aEquip )
{
    BOOL bRet = FALSE;
    m_mapEquips[aEquip->GetItemType()] = aEquip; 
    bRet = TRUE;
    return bRet;
}

CEquipment * CPlayer::GetEquipment( ITEM_TYPE aItemType )
{
    return m_mapEquips[aItemType];
}

INT CPlayer::GetTotalBonus( BONUS_TYPE aBonusType )
{
    INT nRet = 0;
    CEquipment * pMainWeapon = m_mapEquips[ITEM_MAIN_WEAPON];
    for ( auto it = m_mapEquips.begin() ; it != m_mapEquips.end() ; it++ )
    {
        CEquipment * pEquip = it->second;
        if ( pEquip->GetItemType() != ITEM_SUB_WEAPON )
        {
            nRet += pEquip->GetBonusValue( aBonusType );

            for ( size_t i = 0 ; i < EQUIP_MAX_SLOT_CNT ; i++ )
            {
                if ( pEquip->GetXtal(i) != NULL )
                {
                    nRet += pEquip->GetXtal(i)->GetBonusValue( aBonusType );
                }
            }
        }
        else
        {
            if ( pEquip->GetEquipType() == EQUIP_ARROW ||
                 pEquip->GetEquipType() == EQUIP_SHIELD ||
                 pEquip->GetEquipType() == EQUIP_KNIFE )
            {
                nRet += pEquip->GetBonusValue( aBonusType );
            }
            else if ( pMainWeapon->GetEquipType() == EQUIP_ONE_HAND_SWORD && 
                 pEquip->GetEquipType() == EQUIP_ONE_HAND_SWORD && 
                 aBonusType == BONUS_ELEMENT_ATK_RATE )
            {
                nRet += pEquip->GetBonusValue( aBonusType );
            }
            else {}
        }
    }

    
    
    //Hard code passive skill temporarily
    switch ( aBonusType )
    {
        case BONUS_ATK_RATE :
        {
            nRet += 3;
            break;
        }
        case BONUS_ATK :
        {
            nRet += (INT)( m_mapProps[PLAYER_LV] * 0.05 );
            break;
        }
        case BONUS_WEAPON_ATK_RATE :
        {
            nRet += ( 3 * 8 );
            break;
        }
        case BONUS_CRT_DAMAGE :
        {
            nRet += 5;
            break;
        }
        case BONUS_CRT :
        {
            nRet += 5;
            break;
        }
        case BONUS_MAX_HP_RATE :
        {
            nRet += ( 2 * 10 );
            break;
        }
        case BONUS_MAX_HP :
        {
            nRet += ( 100 * 10 );
            break;
        }
        case BONUS_MAX_MP :
        {
            nRet += ( 30 * 10 );
            break;
        }
        default :
        {
            break;
        }
    }


    //string strTmp;
    //CBonusParser::GetInstasnce()->GetBonusDisplayString( aBonusType , nRet , strTmp );
    //wprintf_s( L"TotalBonus: %hs\n" , strTmp.c_str() );
    return nRet;
}