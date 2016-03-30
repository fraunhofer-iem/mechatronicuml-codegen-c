package org.muml.codegen.c.helper;

import org.eclipse.emf.ecore.EObject;
import org.muml.pim.common.naming.*;

	public class NamingHelper {
		
		public static final QualifiedNameProvider nameProvider = new MumlQualifiedNameProvider();
		
		public String getName(EObject obj){
			String name = nameProvider.getQualifiedName(obj).toString();
			
			return name;
		}
		
		
	}