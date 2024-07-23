#encoding: UTF-8
require_relative 'SpaceStation'
require_relative 'SuppliesPackage'
require_relative 'Hangar'
require_relative 'Weapon'
require_relative 'WeaponType'
require_relative 'ShieldBooster'
require_relative 'SpecificDamage'



module Test 
    
    class Examen3

        include Deepspace

        def principal

            #Pregunta 2********************************************************************

            #Pregunta 2.a------------------------------------------------------------------

            station= SpaceStation.new("Leandro", SuppliesPackage.new(2,5,3))

            puts "(2.a) \n" + station.getUIversion.to_s+ "\n\n"

            #Pregunta 2.b------------------------------------------------------------------

            hangar=Hangar.new(3)
            station.receiveHangar(hangar)

            puts "(2.b) \n" + station.getUIversion.to_s+ "\n\n"

            #Pregunta 2.c------------------------------------------------------------------

            weapon=Weapon.new("Espada",WeaponType::LASER,1)
            station.receiveWeapon(weapon)

            puts "(2.c) \n" + station.getUIversion.to_s+ "\n\n"

            #Pregunta 2.d------------------------------------------------------------------
            
            3.times do
                station.receiveWeapon(weapon)
            end 
            

            puts "(2.d) \n" + station.getUIversion.to_s+ "\n\n"

            #Pregunta 2.e------------------------------------------------------------------
            2.times do
                station.mountWeapon(0)
            end 

            puts "(2.e) \n" + station.getUIversion.to_s+ "\n\n"


            #Pregunta 2.f------------------------------------------------------------------

            shield=ShieldBooster.new("Escudo",1.5,2)
            station.receiveShieldBooster(shield)

            puts "(2.f) \n" + station.getUIversion.to_s+ "\n\n"


            #Pregunta 2.g------------------------------------------------------------------
            
            2.times do
                station.receiveShieldBooster(shield)
            end
        

            puts "(2.g) \n" + station.getUIversion.to_s+ "\n\n"

            #Pregunta 2.h------------------------------------------------------------------
            station.mountShieldBooster(1)

            puts "(2.h) \n" + station.getUIversion.to_s+ "\n\n"



            #Pregunta 3********************************************************************

            #Pregunta 3.a------------------------------------------------------------------

            damage=SpecificDamage.new([WeaponType::PLASMA,WeaponType::LASER,WeaponType::MISSILE],3)

            #Pregunta 3.b------------------------------------------------------------------
            puts "(3.b) \n" + damage.getUIversion.to_s+ "\n\n"

            #Pregunta 3.c------------------------------------------------------------------

            weapons= []
            weapons << Weapon.new("1",WeaponType::LASER,1)
            weapons << Weapon.new("2",WeaponType::MISSILE,1)
            weapons << Weapon.new("3",WeaponType::LASER,1)

            ajuste= damage.adjust(weapons, Array.new(2))

            puts "(3.c) \n" + ajuste.getUIversion.to_s+ "\n\n"

            #------------------------------------------------------------------------------
        end
    end

    Examen3.new.principal
end

