#pragma once
#include "Player.h"
#include "Item.h"

class CPlayer;
class CCalc
{
    public :
        CCalc( CPlayer * aPlayer ) : m_pPlayer(aPlayer) {}
        virtual ~CCalc() {}

    public :
        virtual INT GetMaxHp();
        virtual INT GetMaxMp();
        virtual INT GetAtkMpRecover();

        virtual INT GetFinalAtk();
        virtual INT GetFinalCrtAtk();
        virtual INT GetFinalAvgAtk();
        virtual INT GetFinalCrt();
        virtual INT GetFinalCrtDmg();

        virtual INT GetAtkByPlayerCapibility() = NULL;
        virtual INT GetMainSkillAtk() = NULL;
        virtual INT GetMainSkillCrtAtk() = NULL;
        virtual INT GetMainSkillAvgAtk() = NULL;
        virtual INT GetMainSkillElementAtk() = NULL;
        virtual INT GetMainSkillCrtElementAtk() = NULL;
        virtual INT GetMainSkillAvgElementAtk() = NULL;

        virtual INT GetAtkByRefinedWeapon();
        virtual INT GetFinalStability();

    protected :
        INT CalcBonus( INT aOrgVal , INT aBonusRate , INT aBonusVal );

    protected :
        CPlayer * m_pPlayer;
        INT m_nSkillRate;
};

class CBowCalc : public CCalc
{
    public :
        CBowCalc( CPlayer * aPlayer ) : CCalc(aPlayer) { m_nSkillRate = ( 300 + 500 ); }
        virtual ~CBowCalc() {}

    public :
        virtual INT GetAtkByPlayerCapibility();
        virtual INT GetMainSkillAtk();
        virtual INT GetMainSkillCrtAtk();
        virtual INT GetMainSkillAvgAtk();
        virtual INT GetMainSkillElementAtk();
        virtual INT GetMainSkillCrtElementAtk();
        virtual INT GetMainSkillAvgElementAtk();

        virtual INT GetAtkByRefinedWeapon();
        virtual INT GetFinalStability();
};

class CBowgunCalc : public CBowCalc
{
    public :
        CBowgunCalc( CPlayer * aPlayer ) : CBowCalc(aPlayer) { m_nSkillRate = ( 300 + 500 + 250 ); }
        virtual ~CBowgunCalc() {}

    public :
        virtual INT GetAtkByPlayerCapibility();

        virtual INT GetMainSkillAvgAtk();
        virtual INT GetMainSkillAvgElementAtk();

        virtual INT GetAtkByRefinedWeapon();
        virtual INT GetFinalStability();
};