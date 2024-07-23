#encoding: UTF-8

require_relative 'Dice'
require_relative 'SpaceStation'
require_relative 'Weapon'
require_relative 'WeaponType'

module Examen

    class ExamenP1P2

        def initialize(name,age)

            @nombre=name
            @edad=age
        end


        def self.examen(age)
            
            default_name="anónimo"
            new(default_name,age)
        end


        def self.principal

            #Pregunta 1------------------------------------------------------------------

            puts ExamenP1P2.new("Leandro",20).inspect
            puts ExamenP1P2.examen(20).inspect + "\n\n"


            #Pregunta 2------------------------------------------------------------------

            dice= Deepspace::Dice.new()
            weapons=[]

            3.times do

                nWeapons= dice.initWithNWeapons

                nWeapons.times do |i|

                    weapons << Deepspace::Weapon.new(i.to_s, Deepspace::WeaponType::PLASMA,1)

                end

            end

            puts "Total weapons: " + weapons.size().to_s

        end

    end

    ExamenP1P2.principal
end
