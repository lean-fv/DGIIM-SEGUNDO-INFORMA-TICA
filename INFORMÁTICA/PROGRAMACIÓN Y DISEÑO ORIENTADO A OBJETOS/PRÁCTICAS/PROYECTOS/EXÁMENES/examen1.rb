#Ruby
#Clase dentro de modulo examen. Dentro del modulo una clase Test. Tiene dos atributos instancia numericos. Un constructor que reciba dos numeros para inicializarlos. Constructor distinto donde unicamente reciba 1 numero y el otro se fija a -1 y constructor de copia. Fuera del modulo examen usar constrcutores.

module Examen

	class Test
	
		def initialize (a,b)
		
			@a=a
			@b=b
		
		end
		
		def self.test1(a,b)
			new(a,b)
		end
		
		
		def self.test2(a)
			new(a,-1)
		end
		
		def a
			@a
		
		end
		
		def b
			@b
		
		end
		
		
		def self.test3(x)
            		new(x.a,x.b)
        	end
        	
	
	end
end

a=Examen::Test.test1(1,2)

b=Examen::Test.test2(3)

c=Examen::Test.test3(a)

puts #{"a"}
puts #{"b"}
puts #{"c"}




