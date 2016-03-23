package org.muml.codegen.c.export.ui;

import org.eclipse.core.resources.IContainer;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.emf.ecore.EObject;


public interface ITargetPlatformGenerator {

	
	public void generateSourceCode(EObject element, IContainer targetFolder, IProgressMonitor monitor);
	
	public String getName();
	
	public String getDescription();
}
