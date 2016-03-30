package org.muml.codegen.c.helper;

import org.muml.pim.valuetype.TimeValue;
	
	public class TimeHelper {
	        public double getFactor(TimeValue timeValue) {
	        		
	        	
	                if (timeValue == null || timeValue.getUnit() == null) {
	                        return 1;
	                }
	                switch (timeValue.getUnit()) {
                case DAYS:
                        return 86400000;
                case HOURS:
	                        return 3600000;
                case MINUTES:
                       return 60000;
                case SECONDS:
	                        return 1000;
	                        
	            case MILLISECONDS:
	                        return 1;
	            case MICROSECONDS:
	                        return Math.pow(10, -3);
	            case NANOSECONDS:
	                        return Math.pow(10, -6);
	                default:
	                        // should not happen
	                        return 1;
	                }
	        }
	}