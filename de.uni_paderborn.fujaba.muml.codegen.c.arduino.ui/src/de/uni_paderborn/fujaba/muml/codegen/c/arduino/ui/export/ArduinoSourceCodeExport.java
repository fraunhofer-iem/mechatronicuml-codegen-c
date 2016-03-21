package de.uni_paderborn.fujaba.muml.codegen.c.arduino.ui.export;

import java.io.IOException;
import java.util.Collections;

import org.eclipse.core.resources.IContainer;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.emf.ecore.EObject;

import de.uni_paderborn.fujaba.muml.codegen.c.arduino.ui.common.GenerateAll;
import de.uni_paderborn.fujaba.muml.codegen.export.ui.ITargetPlatformGenerator;
import de.uni_paderborn.fujaba.muml.instance.ComponentInstanceConfiguration;

public class ArduinoSourceCodeExport implements ITargetPlatformGenerator {

	private String name = "ANSI C99";
	private String description = "Generates C99 code. A GNU-makefile is provided for compiling and linking.";
	
	public void generateSourceCode(EObject element, IContainer targetFolder, IProgressMonitor monitor) {
		// TODO Auto-generated method stub
		ComponentInstanceConfiguration cic = (ComponentInstanceConfiguration) element;
		GenerateAll generator = new GenerateAll(element.eResource().getURI(), targetFolder, Collections.EMPTY_LIST);
		try {
			generator.generateCIC(monitor, cic);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

	public String getName() {
		return this.name;
	}

	public String getDescription() {
		// TODO Auto-generated method stub
		return this.description;
	}

	public String toString(){
		return this.name;
	}


}
