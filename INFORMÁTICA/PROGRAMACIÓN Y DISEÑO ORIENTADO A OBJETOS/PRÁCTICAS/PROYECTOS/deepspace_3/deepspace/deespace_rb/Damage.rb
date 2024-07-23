#encoding: UTF-8

require_relative 'DamageToUI'

module Deepspace

    #Representa el daño producido a una estacion espacial cuando se pierde
    #el combate. Indica la cantidad perdida de escudo y, o una cantidad de tipos
    #indeterminados de armas o un conjunto de tipos de armas concretas a eliminar
    class Damage 
        
        @NOUSE=-1     #Atributo de instancia(porque estoy en ámbito de clase) de clase( necesitamos un consultor para acceder a el en un metodo de instancia)
                        #otra opcion es hacerlo de clase(dos @@)

        #Constructores
        def initialize (w,s,wl)
            @nWeapons=w        #Cantidad de tipos indeterminados de armas
            @nShields=s        #Cantidad perdida de escudo
            @weapons=wl        #Conjunto de tipos de armas concretas a eliminar
        end

        #Necesitamos un metodo de clase para acceder al altributo de instancia
        def self.NOUSE    
            @NOUSE
        end

        def self.newNumericWeapons(w, s)
            return new(w,s,nil)             #Mejor crearlo a nil antes que un array vacio
        end

        def self.newSpecificWeapons(wl, s)
            return new(Damage.NOUSE,s,wl)
        end


        #Getters
        def nWeapons
            @nWeapons
        end

        def nShields
            @nShields
        end

        def weapons
            @weapons
        end

        #Constructor de copia.
        #En este caso Todas las instancias deben ser unas independientes de otras y por lo tanto no deben compartir
        #instancias de objetos mutables(modificables)
        #Por lo tanto, debemos crear un nuevo Array para que no compartan el mismo ambas instancias, si los objetos del array del
        #pudiesen ser modificados, también habria que crear uno nuevo para cado uno, en este caso no porque son WeaponType(no 
        #se pueden modificar)
        def self.newCopy(d)
            
            if(d.nWeapons==Damage.NOUSE)
                weapons_copia=Array.new(d.weapons)
                return Damage.newSpecificWeapons(d.weapons, d.nShields)
            else
                return Damage.newNumericWeapons(d.nWeapons,d.nShields)
            end
        end

        #Capa que permite conectar el modelo con la interfaz de 
        #usuario manteniendo cierto nivel de aislamiento
        def getUIversion()
            return (DamageToUI.new(self))
        end  

        #Devuelve el indice de la primera arma de w, cuyo tipo coincida con t.
        # Si no se encuentra devuelve -1
        def arrayContainsType(w,t)
            index=Damage.NOUSE   #Si pusiesemos index=@NOUSE NOUSE seria otra variable distinta, en este caso de instancia
            i=0
            seguir=true
            while i<w.size() && seguir
                if(w.at(i).type==t)
                    index=i
                    seguir=false  #Para salirnos del bucle
                end
                i += 1
                
            end        
            
               
            return index
        end

        #Devuelve una versión ajustada del objeto a w y s.
        #Se devuelve una copia del mismo pero reducida si es necesario para que no 
        #implique perder armas o potenciadores de escudos que no están en las
        #colecciones de los parámetros.

        #@param w Array de weapons.
        #@param s Array de shieldBoosters
        
    
        def adjust(w, s)
            
        
            #Ajustamos los escudos
            #if(@nShields>s.size)
            #    shields_copia=s.size()
            #else
            #    shields_copia=@nShields
            #end

            shields_copia = [@nShields, s.size].min

            #Ajustamos las armas
            if(@nWeapons==Damage.NOUSE)    #Trabajamos con el vector: Comprobamos si no esta vacio
                weapons_copia=Array.new()      #Array donde vamos a almacenar la solucion
                w_aux=Array.new(w)
                
    
                #Si un tipo de arma esta en w_aux la añadimos a weapons_copia,
                #si no esta no la añadimos ya que entonces perderiamos tipos de armas
                #que no estan en w
            

                @weapons.each do |element|
                    indice=arrayContainsType(w_aux, element)
                    #Si el tipo de weapon esta en el array w_aux la añadimos a las
                    #armas que se pueden perder(las de damage)
                    if(indice!=-1)
                        
                        weapons_copia.push(element)
                        w_aux.delete_at(indice)  #Lo borramos porque ya hemos encontrado este tipo de arma
                    end
                end
                
                return Damage.newSpecificWeapons(weapons_copia,shields_copia)
                
            else
               
                weapons_copia= [@nWeapons, w.size].min
                return Damage.newNumericWeapons(weapons_copia, shields_copia)
                
            end
            
        end

        #Si la instancia dispone de una lista de tipos concretos de armas, intenta 
        #eliminar el tipo del arma pasada como parámetro de esa lista. 
        #En otro caso simplemente decrementa en una unidad el contador de armas que 
        #deben ser eliminadas. 
    
        #Ese contador no puede ser inferior a cero en ningún caso
        def discardWeapon(w)
            if (@weapons!=nil) 
                i= @weapons.index(w.type)     #Devuelve el primer indice que tiene el objeto(el ultimo con rindex)
                if (i!=nil) 
                    #Devuelve el elemento eliminado.
                    @weapons.delete_at(i)
                end
            elsif(@nWeapons>0)
                @nWeapons-=1
            end

        end

        #Decrementa en una unidad el número de potenciadores de escudo que deben ser 
        #eliminados.
        #Ese contador no puede ser inferior a cero en ningún caso
        def discardShieldBooster
            if (@nShields>0)
                @nShields-=1
            end
        end

        #Devuelve true si el daño no implica la pérdida de ningún tipo de accesorio 
        #(armas o potenciadores de escudo).
        def hasNoEffect
            
        
            if (@nWeapons==self.class.NOUSE) 
                
                output = (@weapons.size == 0 && @nShields==0)

            else output=(@nWeapons==0 && @nShields==0)

            end

            return output
        end

        def to_s()
        
            weapons_string= "Weapons: "
            for i in 0..(@weapons.size-1) do
                weapons_string += @weapons.at(i).to_s() + "\n"
            end
            
            output="\nDamage attributes:"
            output+= "\nnWeapons=" +@nWeapons.to_s
            output+= "\nnShields=" +@nShields.to_s + "\n"
            output+= weapons_string + "\n"

            return output

        end

    end
end
