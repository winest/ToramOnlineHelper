#include "stdafx.h"
#include "Calc.h"

INT CCalc::GetMaxHp()
{
    INT nPlayerLv = m_pPlayer->GetProperty( PLAYER_LV );
    INT nVit = m_pPlayer->GetProperty( PLAYER_VIT );
    INT nHp = 100;
    nHp = (INT)( ((93.0f + ((nPlayerLv * 321.0f) / 100.0f)) + ((nPlayerLv * nVit) / 3.0f)) + (nPlayerLv * 4.26f) );
    nHp = CalcBonus( nHp , m_pPlayer->GetTotalBonus( BONUS_MAX_HP_RATE ) , m_pPlayer->GetTotalBonus( BONUS_MAX_HP ) );
    return min( nHp , 99999 );
}

INT CCalc::GetMaxMp()
{
    INT nPlayerLv = m_pPlayer->GetProperty( PLAYER_LV );
    INT nInt = m_pPlayer->GetProperty( PLAYER_INT );
    INT nTec = m_pPlayer->GetProperty( PLAYER_TEC );
    INT nMp = ( ((99 + nPlayerLv) + (nInt / 10)) + nTec );
    nMp = CalcBonus( nMp , m_pPlayer->GetTotalBonus( BONUS_MAX_MP_RATE ) , m_pPlayer->GetTotalBonus( BONUS_MAX_MP ) );
    return min( max( 0 , nMp ) , 2000 );
}

INT CCalc::GetAtkMpRecover()
{
    INT nMp = this->GetMaxMp();
    INT nAtkMpRecover = ( nMp / 100 ) + m_pPlayer->GetTotalBonus( BONUS_ATK_MP_RECOVER );
    return nAtkMpRecover;
}

INT CCalc::GetFinalAtk()
{
    INT nAtk = this->GetAtkByPlayerCapibility() + this->GetAtkByRefinedWeapon();
    nAtk = CalcBonus( nAtk , m_pPlayer->GetTotalBonus(BONUS_ATK_RATE) , m_pPlayer->GetTotalBonus(BONUS_ATK) );
    return nAtk;
}

INT CCalc::GetFinalCrtAtk()
{
    return ( this->GetFinalAtk() * this->GetFinalCrtDmg() ) / 100;
}

INT CCalc::GetFinalAvgAtk()
{
    INT nCrt = this->GetFinalCrt();
    INT nAvgAtk = ( this->GetFinalAtk() * (100-nCrt) ) / 100 + ( this->GetFinalCrtAtk() * nCrt ) / 100;
    return (INT)( nAvgAtk * (( 100 + this->GetFinalStability() )/(double)200) );
}

INT CCalc::GetFinalCrt()
{
    INT nCrt = m_pPlayer->GetProperty( PLAYER_CRT );
    nCrt = CalcBonus( 25 + INT(nCrt/3.4f) , m_pPlayer->GetTotalBonus(BONUS_CRT_RATE) , m_pPlayer->GetTotalBonus(BONUS_CRT) );
    return min( max( 0 , nCrt ) , 100 );
}

INT CCalc::GetFinalCrtDmg()
{
    INT nStr = m_pPlayer->GetProperty( PLAYER_STR );
    return CalcBonus( 150 + INT(nStr/5.1f) , m_pPlayer->GetTotalBonus(BONUS_CRT_DAMAGE_RATE) , m_pPlayer->GetTotalBonus(BONUS_CRT_DAMAGE) );
}

INT CCalc::GetAtkByRefinedWeapon()
{
    INT nAtk = 0 , nRefineLv = 0 , nStability = 0;
    CEquipment * pMainWeapon = m_pPlayer->GetEquipment( ITEM_MAIN_WEAPON );
    pMainWeapon->GetProperty( nAtk , nRefineLv , nStability );

    INT nAtkForWeapon = CalcBonus( nAtk , m_pPlayer->GetTotalBonus(BONUS_WEAPON_ATK_RATE) , m_pPlayer->GetTotalBonus(BONUS_WEAPON_ATK) );

    //( nAtk * nRefineLv * nRefineLv ) is correct 
    INT nAtkAfterRefine = ( nAtkForWeapon + nRefineLv ) + (INT)( ( nAtk * nRefineLv * nRefineLv ) / (double)100 );

    return nAtkAfterRefine;
}

INT CCalc::GetFinalStability()
{
    INT nAtk = 0 , nRefineLv = 0 , nStability = 0;
    CEquipment * pMainWeapon = m_pPlayer->GetEquipment( ITEM_MAIN_WEAPON );
    pMainWeapon->GetProperty( nAtk , nRefineLv , nStability );

    INT nBonusStability = m_pPlayer->GetTotalBonus( BONUS_STABILITY_RATE );
    return min( max( 0 , nStability + nBonusStability ) , 100 ); 
}

INT CCalc::CalcBonus( INT aOrgVal , INT aBonusRate , INT aBonusVal )
{
    return (INT)( aOrgVal * ((100 + aBonusRate)/(double)100) ) + aBonusVal;
}








INT CBowCalc::GetAtkByPlayerCapibility()
{
    INT nPlayerLv = m_pPlayer->GetProperty( PLAYER_LV );
    INT nStr = m_pPlayer->GetProperty( PLAYER_STR );
    INT nDex = m_pPlayer->GetProperty( PLAYER_DEX );

    nStr = CalcBonus( nStr , m_pPlayer->GetTotalBonus(BONUS_STR_RATE) , m_pPlayer->GetTotalBonus(BONUS_STR) );
    nDex = CalcBonus( nDex , m_pPlayer->GetTotalBonus(BONUS_DEX_RATE) , m_pPlayer->GetTotalBonus(BONUS_DEX) );
    return nPlayerLv + nStr + ( nDex * 3 );
}

INT CBowCalc::GetMainSkillAtk()
{
    INT nAtk = this->GetFinalAtk() + 200 + 200;
    nAtk = (INT)( nAtk * (m_nSkillRate / (double)100) );
    return nAtk;
}

INT CBowCalc::GetMainSkillCrtAtk()
{
    INT nAtk = this->GetFinalAtk() + 200 + 200;
    nAtk = (INT)( nAtk * (this->GetFinalCrtDmg() / (double)100) );
    nAtk = (INT)( nAtk * (m_nSkillRate / (double)100) );
    return nAtk;
}

INT CBowCalc::GetMainSkillAvgAtk()
{
    INT nCrt = this->GetFinalCrt();
    INT nAvgAtk = ( this->GetMainSkillAtk() * (100-nCrt) ) / 100 + ( this->GetMainSkillCrtAtk() * nCrt ) / 100;
    return (INT)( nAvgAtk * (( 100 + this->GetFinalStability() )/(double)200) );
}

INT CBowCalc::GetMainSkillElementAtk()
{
    INT nElementAtkRate = m_pPlayer->GetTotalBonus( BONUS_ELEMENT_ATK_RATE );
    INT nAtk = this->GetFinalAtk() + 200 + 200;
    nAtk = (INT)( nAtk * ((100 + nElementAtkRate) / (double)100 ) );
    nAtk = (INT)( nAtk * (m_nSkillRate / (double)100) );
    return nAtk;
}

INT CBowCalc::GetMainSkillCrtElementAtk()
{
    INT nElementAtkRate =  m_pPlayer->GetTotalBonus( BONUS_ELEMENT_ATK_RATE );
    INT nAtk = this->GetFinalAtk() + 200 + 200;
    nAtk = (INT)( nAtk * (this->GetFinalCrtDmg() / (double)100) );
    nAtk = (INT)( nAtk * ((100 + nElementAtkRate) / (double)100 ) );
    nAtk = (INT)( nAtk * (m_nSkillRate / (double)100) );
    return nAtk;
}

INT CBowCalc::GetMainSkillAvgElementAtk()
{
    INT nCrt = this->GetFinalCrt();
    INT nAvgAtk = ( this->GetMainSkillElementAtk() * (100-nCrt) ) / 100 + ( this->GetMainSkillCrtElementAtk() * nCrt ) / 100;
    return (INT)( nAvgAtk * (( 100 + this->GetFinalStability() )/(double)200) );
}

INT CBowCalc::GetAtkByRefinedWeapon()
{
    INT nMainWeaponAtk = 0 , nMainWeaponRefineLv = 0 , nMainWeaponStability = 0;
    INT nSubWeaponAtk = 0 , nSubWeaponRefineLv = 0 , nSubWeaponStability = 0;
    CEquipment * pMainWeapon = m_pPlayer->GetEquipment( ITEM_MAIN_WEAPON );
    CEquipment * pSubWeapon = m_pPlayer->GetEquipment( ITEM_SUB_WEAPON );
    if ( pMainWeapon != NULL )
    {
        pMainWeapon->GetProperty( nMainWeaponAtk , nMainWeaponRefineLv , nMainWeaponStability );
    }
    if ( pSubWeapon != NULL )
    {
        pSubWeapon->GetProperty( nSubWeaponAtk , nSubWeaponRefineLv , nSubWeaponStability );
    }

    INT nAtkForWeapon = CalcBonus( nMainWeaponAtk , m_pPlayer->GetTotalBonus(BONUS_WEAPON_ATK_RATE) , m_pPlayer->GetTotalBonus(BONUS_WEAPON_ATK) );
    INT nAtkAfterRefine = ( nAtkForWeapon + nMainWeaponRefineLv ) + (INT)( ( nMainWeaponAtk * nMainWeaponRefineLv * nMainWeaponRefineLv ) / (double)100 );

    return nAtkAfterRefine + nSubWeaponAtk;
}

INT CBowCalc::GetFinalStability()
{
    INT nStr = m_pPlayer->GetProperty( PLAYER_STR );
    INT nDex = m_pPlayer->GetProperty( PLAYER_DEX );

    INT nMainWeaponAtk = 0 , nMainWeaponRefineLv = 0 , nMainWeaponStability = 0;
    INT nSubWeaponAtk = 0 , nSubWeaponRefineLv = 0 , nSubWeaponStability = 0;
    CEquipment * pMainWeapon = m_pPlayer->GetEquipment( ITEM_MAIN_WEAPON );
    CEquipment * pSubWeapon = m_pPlayer->GetEquipment( ITEM_SUB_WEAPON );
    if ( pMainWeapon != NULL )
    {
        pMainWeapon->GetProperty( nMainWeaponAtk , nMainWeaponRefineLv , nMainWeaponStability );
    }
    if ( pSubWeapon != NULL )
    {
        pSubWeapon->GetProperty( nSubWeaponAtk , nSubWeaponRefineLv , nSubWeaponStability );
    }
    
    INT nBonusStability = m_pPlayer->GetTotalBonus( BONUS_STABILITY_RATE );
    return nMainWeaponStability + nSubWeaponStability + (INT)( ( nStr * 0.5f + nDex * 0.5f ) / (double)10 ) + nBonusStability;
}






INT CBowgunCalc::GetAtkByPlayerCapibility()
{
    INT nPlayerLv = m_pPlayer->GetProperty( PLAYER_LV );
    INT nDex = m_pPlayer->GetProperty( PLAYER_DEX );

    nDex = CalcBonus( nDex , m_pPlayer->GetTotalBonus(BONUS_DEX_RATE) , m_pPlayer->GetTotalBonus(BONUS_DEX) );
    return nPlayerLv + ( nDex * 4 );
}

INT CBowgunCalc::GetMainSkillAvgAtk()
{
    INT nCrt = (INT)( this->GetFinalCrt() * 0.75f );
    INT nAvgAtk = ( this->GetMainSkillAtk() * (100-nCrt) ) / 100 + ( this->GetMainSkillCrtAtk() * nCrt ) / 100;
    return (INT)( nAvgAtk * (( 100 + this->GetFinalStability() )/(double)200) );
}

INT CBowgunCalc::GetMainSkillAvgElementAtk()
{
    INT nCrt = (INT)( this->GetFinalCrt() * 0.75f );
    INT nAvgAtk = ( this->GetMainSkillElementAtk() * (100-nCrt) ) / 100 + ( this->GetMainSkillCrtElementAtk() * nCrt ) / 100;
    return (INT)( nAvgAtk * (( 100 + this->GetFinalStability() )/(double)200) );
}

INT CBowgunCalc::GetAtkByRefinedWeapon()
{
    INT nMainWeaponAtk = 0 , nMainWeaponRefineLv = 0 , nMainWeaponStability = 0;
    INT nSubWeaponAtk = 0 , nSubWeaponRefineLv = 0 , nSubWeaponStability = 0;
    CEquipment * pMainWeapon = m_pPlayer->GetEquipment( ITEM_MAIN_WEAPON );
    CEquipment * pSubWeapon = m_pPlayer->GetEquipment( ITEM_SUB_WEAPON );
    if ( pMainWeapon != NULL )
    {
        pMainWeapon->GetProperty( nMainWeaponAtk , nMainWeaponRefineLv , nMainWeaponStability );
    }
    if ( pSubWeapon != NULL )
    {
        pSubWeapon->GetProperty( nSubWeaponAtk , nSubWeaponRefineLv , nSubWeaponStability );
    }

    INT nAtkForWeapon = CalcBonus( nMainWeaponAtk , m_pPlayer->GetTotalBonus(BONUS_WEAPON_ATK_RATE) , m_pPlayer->GetTotalBonus(BONUS_WEAPON_ATK) );
    INT nAtkAfterRefine = ( nAtkForWeapon + nMainWeaponRefineLv ) + (INT)( ( nMainWeaponAtk * nMainWeaponRefineLv * nMainWeaponRefineLv ) / (double)100 );

    return nAtkAfterRefine + ( nSubWeaponAtk / 2 );
}

INT CBowgunCalc::GetFinalStability()
{
    INT nStr = m_pPlayer->GetProperty( PLAYER_STR );

    INT nMainWeaponAtk = 0 , nMainWeaponRefineLv = 0 , nMainWeaponStability = 0;
    INT nSubWeaponAtk = 0 , nSubWeaponRefineLv = 0 , nSubWeaponStability = 0;
    CEquipment * pMainWeapon = m_pPlayer->GetEquipment( ITEM_MAIN_WEAPON );
    CEquipment * pSubWeapon = m_pPlayer->GetEquipment( ITEM_SUB_WEAPON );
    if ( pMainWeapon != NULL )
    {
        pMainWeapon->GetProperty( nMainWeaponAtk , nMainWeaponRefineLv , nMainWeaponStability );
    }
    if ( pSubWeapon != NULL )
    {
        pSubWeapon->GetProperty( nSubWeaponAtk , nSubWeaponRefineLv , nSubWeaponStability );
    }
    
    INT nBonusStability = m_pPlayer->GetTotalBonus( BONUS_STABILITY_RATE );
    return nMainWeaponStability + (nSubWeaponStability/2) + (INT)( (nStr * 0.5f) / (double)10 ) + nBonusStability;
}