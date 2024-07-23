#encoding: UTF-8
require_relative 'LootToUI'

module Deepspace

    class Loot
        def initialize (nSupplies, nWeapons, nShields, nHangars, nMedals)

            @nSupplies=nSupplies
            @nWeapons=nWeapons
            @nShields=nShields
            @nHangars=nHangars
            @nMedals=nMedals
        end

        def nSupplies
            @nSupplies
        end

        def nWeapons
            @nWeapons
        end

        def nShields
            @nShields
        end

        def nHangars
            @nHangars
        end

        def nMedals
            @nMedals
        end

        #Capa que permite conectar el modelo con la interfaz de 
        #usuario manteniendo cierto nivel de aislamiento
        def getUIversion()
            return (LootToUI.new(self))
        end  
        

        #Metodo publico, devuelve una representación en forma
        # de cadena de caracteres de una instancia
        def to_s()
            
            output="\nLoot attributes:"
            output+= "\nnSupplies=" +nSupplies.to_s
            output+="\nnWeapons=" +nWeapons.to_s
            output+= "\nnShields=" +nShields.to_s
            output+= "\nnHangars=" +nHangars.to_s
            output+= "\nnMedals="  +nMedals.to_s

            return output
            
        end
    end

end

#prueba = Deepspace::Loot.new(1,1,1,1,1)
#puts prueba.to_s