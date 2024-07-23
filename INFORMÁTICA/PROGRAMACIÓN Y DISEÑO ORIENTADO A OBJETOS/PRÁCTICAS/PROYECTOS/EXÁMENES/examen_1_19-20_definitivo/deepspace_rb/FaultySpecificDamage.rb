#encoding: UTF-8
require_relative 'SpecificDamage'
require_relative 'Dice'

module Deepspace

    class FaultySpecificDamage < SpecificDamage

        def initialize(wl,s)

            super(wl,s)

            @dice=Dice.new()
        end

        #Override
        def adjust(w,s)

            ajuste= super(w,s)
            type =@dice.faultyDamage
            if (!type.nil?)

                ajuste.weapons.each do |weapon|
                    if (weapon==type)
                        ajuste.discardWeapon(Weapon.new("arma",type,1))
                    end
                end
            end

            return ajuste
            
        end
        
    end

end

