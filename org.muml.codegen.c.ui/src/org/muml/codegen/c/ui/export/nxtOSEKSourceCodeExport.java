package org.muml.codegen.c.ui.export;

import java.io.IOException;
import java.util.Collections;

import org.eclipse.core.resources.IContainer;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.emf.ecore.EObject;
import org.muml.codegen.c.export.ui.ITargetPlatformGenerator;
import org.muml.codegen.c.ui.common.GenerateAllnxtOSEK;
import org.muml.pim.instance.ComponentInstanceConfiguration;

public class nxtOSEKSourceCodeExport implements ITargetPlatformGenerator {

	private String name = "nxtOSEK (RTOS for LEGO Mindstorms";
	private String description = "Generates source code for nxtOSEK. This includes all needed .OIL files.";
	public void generateSourceCode(EObject element, IContainer targetFolder, IProgressMonitor monitor) {
		

		ComponentInstanceConfiguration cic = (ComponentInstanceConfiguration) element;
		GenerateAllnxtOSEK generator = new GenerateAllnxtOSEK(element.eResource().getURI(), targetFolder, Collections.EMPTY_LIST);
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



}
