#encoding: UTF-8

require_relative 'CardDealer'
require_relative 'SpaceStation'
require_relative 'GameUniverse'

module Prueba

    class Examen

        def self.main


            dealer = Deepspace::CardDealer.instance

            sp=dealer.nextSuppliesPackage
            weapon=dealer.nextWeapon
            sb=dealer.nextShieldBooster
            hangar=dealer.nextHangar
            enemy=dealer.nextEnemy

            puts sp.class
            puts weapon.class
            puts sb.class
            puts hangar.class
            puts enemy.class
            puts "----------------------------------------------------------------\n\n"

            station= Deepspace::SpaceStation.new("Leandro",sp)
            station.receiveHangar(hangar)
            station.receiveWeapon(weapon)
            station.receiveShieldBooster(sb)

            puts station.getUIversion.to_s
            puts "----------------------------------------------------------------\n\n"

            station.mountWeapon(0)
            station.mountShieldBooster(0)

            puts station.getUIversion.to_s
            puts "----------------------------------------------------------------\n\n"


            game= Deepspace::GameUniverse.new()
            names= []
            names << "Leandro"

            game.init(names)
            result=game.combatGo(station,enemy)
            puts "Combat Result: " + result.to_s
            puts "----------------------------------------------------------------\n\n"

            puts self.name


        end
    end

    Examen.main
end
