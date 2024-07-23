#encoding: UTF-8
require_relative 'FaultySpecificDamage'
require_relative 'WeaponType'
require_relative 'Weapon'

module Deepspace

    class ExamenP4
        def main

            damage=FaultySpecificDamage.new([WeaponType::ROCA, WeaponType::ASTEROIDE, \
            WeaponType::ACIDO,WeaponType::ROCA],10)

            array=[]
            array <<Weapon.new("arma",WeaponType::ACIDO,1)
            array <<Weapon.new("arma",WeaponType::ROCA,1)
            array <<Weapon.new("arma",WeaponType::ACIDO,1)


            ajuste=damage.adjust(array,[])

            puts damage.getUIversion.to_s
            puts ajuste.getUIversion.to_s


        end
    end

    ExamenP4.new.main

end


