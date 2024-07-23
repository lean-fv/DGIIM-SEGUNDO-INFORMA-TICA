#encoding: UTF-8

require_relative 'NumericDamage'
require_relative 'SpecificDamage'
require_relative 'WeaponType'
require_relative 'Weapon'
require_relative 'ShieldBooster'


module P3

    class ExamenP3

    #include Deepspace

        def self.principal

            nDamage=Deepspace::NumericDamage.new(2,3)
            

            types= Array.new
            types.push(Deepspace::WeaponType::LASER)
            types.push(Deepspace::WeaponType::LASER)
            types.push(Deepspace::WeaponType::PLASMA)

            sDamage=Deepspace::SpecificDamage.new(types,0)

            #---------------------------------------------

            n_array_w=Array.new()
            n_array_w.push(Deepspace::Weapon.new("1",Deepspace::WeaponType::PLASMA,1))
            n_array_w.push(Deepspace::Weapon.new("2",Deepspace::WeaponType::PLASMA,1))
            n_array_w.push(Deepspace::Weapon.new("3",Deepspace::WeaponType::LASER,1))
            n_array_w.push(Deepspace::Weapon.new("4",Deepspace::WeaponType::LASER,1))
            n_array_w.push(Deepspace::Weapon.new("5",Deepspace::WeaponType::LASER,1))

            n_array_s=Array.new()
            n_array_s.push(Deepspace::ShieldBooster.new("1",1,1))
            n_array_s.push(Deepspace::ShieldBooster.new("2",1,1))


            ajuste1=nDamage.adjust(n_array_w,n_array_s)


            s_array_w=Array.new()
            s_array_w.push(Deepspace::Weapon.new("1",Deepspace::WeaponType::PLASMA,1))
            s_array_w.push(Deepspace::Weapon.new("2",Deepspace::WeaponType::PLASMA,1))
            s_array_w.push(Deepspace::Weapon.new("3",Deepspace::WeaponType::LASER,1))
            s_array_w.push(Deepspace::Weapon.new("4",Deepspace::WeaponType::LASER,1))
            s_array_w.push(Deepspace::Weapon.new("5",Deepspace::WeaponType::MISSILE,1))
            s_array_w.push(Deepspace::Weapon.new("6",Deepspace::WeaponType::MISSILE,1))


            ajuste2=sDamage.adjust(s_array_w,Array.new)

            puts ajuste1.getUIversion.to_s
            puts ajuste2.getUIversion.to_s

            #--------------------------------------------------------------

        end

    end

    ExamenP3.principal

end