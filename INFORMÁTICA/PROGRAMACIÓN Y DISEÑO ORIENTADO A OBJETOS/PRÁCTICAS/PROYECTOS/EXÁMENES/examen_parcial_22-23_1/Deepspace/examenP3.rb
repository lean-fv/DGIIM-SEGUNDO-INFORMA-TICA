#encoding: UTF-8

require_relative 'SpecificDamage'
require_relative 'WeaponType'
require_relative 'SpaceStation'
require_relative 'SuppliesPackage'
require_relative 'Loot'

module Deepspace

    class Examen

        def main

            damage= SpecificDamage.new([WeaponType::LASER,WeaponType::MISSILE,WeaponType::MISSILE, \
                    WeaponType::PLASMA,WeaponType::PLASMA,WeaponType::PLASMA],0)

            puts damage.getUIversion.to_s + "\n---------------------------------------\n\n"



            station= SpaceStation.new("Leandro", SuppliesPackage.new(0,0,0))

            station.setLoot(Loot.new(0,0,0,1,0))

            puts station.getUIversion.to_s + "\n---------------------------------------\n\n"



            3.times do |i|

                station.receiveWeapon(Weapon.new(i.to_s,WeaponType::LASER,1))
                station.mountWeapon(0)
            end

            2.times do |i|

                station.receiveWeapon(Weapon.new(i.to_s,WeaponType::MISSILE,1))
                station.mountWeapon(0)
            end

            station.receiveWeapon(Weapon.new("1",WeaponType::PLASMA,1))
            station.mountWeapon(0)

            puts station.getUIversion.to_s + "\n---------------------------------------\n\n"



            station.setPendingDamage(damage)

            puts station.getUIversion.to_s + "\n---------------------------------------\n\n"

        end
    end

    Examen.new.main
end
