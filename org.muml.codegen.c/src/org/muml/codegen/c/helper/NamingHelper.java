package org.muml.codegen.c.helper;

import de.uni_paderborn.fujaba.muml.common.naming.*;
import org.eclipse.emf.ecore.EObject;

	public class NamingHelper {
		
		public static final QualifiedNameProvider nameProvider = new MumlQualifiedNameProvider();
		
		public String getName(EObject obj){
			String name = nameProvider.getQualifiedName(obj).toString();
			
			return name;
		}
		
		
	}