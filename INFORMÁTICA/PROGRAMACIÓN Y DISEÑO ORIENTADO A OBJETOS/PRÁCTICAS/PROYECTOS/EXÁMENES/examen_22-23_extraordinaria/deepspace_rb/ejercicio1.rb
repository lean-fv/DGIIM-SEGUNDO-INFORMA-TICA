#encoding: UTF-8
require_relative 'SpaceCity'
require_relative 'CardDealer'
require_relative 'SpaceStation'

module Deepspace
	
	class Ejercicio1
	
		def main
			dealer= CardDealer.instance
			collaborators= []
			
			
			collaborators.push(SpaceStation.new("Station",dealer.nextSuppliesPackage))
			collaborators.push(SpaceStation.new("Station",dealer.nextSuppliesPackage))
			collaborators.push(SpaceStation.new("Station",dealer.nextSuppliesPackage))
			
			
			city = SpaceCity.new(collaborators)
			
			copy= SpaceCity.copy(city)
			copy.fire
		end
	
	
	end
	
	Ejercicio1.new.main
	
	
end
