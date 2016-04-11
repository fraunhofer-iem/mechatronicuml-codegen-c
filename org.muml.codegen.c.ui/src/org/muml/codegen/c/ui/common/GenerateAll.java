/*******************************************************************************
 * Copyright (c) 2008, 2012 Obeo.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 * 
 * Contributors:
 *     Obeo - initial API and implementation
 *******************************************************************************/
package org.muml.codegen.c.ui.common;

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URISyntaxException;
import java.net.URL;
import java.net.URLDecoder;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;

import org.apache.commons.io.FileUtils;
import org.eclipse.core.resources.IContainer;
import org.eclipse.core.runtime.FileLocator;
import org.eclipse.core.runtime.IPath;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.Path;
import org.eclipse.core.runtime.Platform;
import org.eclipse.emf.common.util.BasicMonitor;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.gmf.runtime.notation.Diagram;
import org.muml.core.ExtendableElement;
import org.muml.core.modelinstance.ModelElementCategory;
import org.muml.core.modelinstance.RootNode;
import org.muml.pim.instance.ComponentInstanceConfiguration;
import org.osgi.framework.Bundle;

/**
 * Main entry point of the 'C' generation module.
 */
public class GenerateAll {

	/**
	 * The model URI.
	 */
	private URI modelURI;

	/**
	 * The output folder.
	 */
	private IContainer targetFolder;

	/**
	 * The other arguments.
	 */
	List<? extends Object> arguments;

	/**
	 * Constructor.
	 * 
	 * @param modelURI
	 *            is the URI of the model.
	 * @param targetFolder
	 *            is the output folder
	 * @param arguments
	 *            are the other arguments
	 * @throws IOException
	 *             Thrown when the output cannot be saved.
	 * @generated
	 */
	public GenerateAll(URI modelURI, IContainer targetFolder, List<? extends Object> arguments) {
		this.modelURI = modelURI;
		this.targetFolder = targetFolder;
		this.arguments = arguments;
	}

	/**
	 * Launches the generation.
	 *
	 * @param monitor
	 *            This will be used to display progress information to the user.
	 * @throws IOException
	 *             Thrown when the output cannot be saved.
	 * @generated NOT
	 */
	public void doGenerate(IProgressMonitor monitor) throws IOException {
		if (!targetFolder.getLocation().toFile().exists()) {
			targetFolder.getLocation().toFile().mkdirs();
		}

		// final URI template0 =
		// getTemplateURI("org.muml.codegen.c", new
		// Path("/de/uni_paderborn/fujaba/muml/model/gen/c/main/main.emtl"));
		// org.muml.codegen.c.main.Main gen0 = new
		// org.muml.codegen.c.main.Main(modelURI,
		// targetFolder.getLocation().toFile(), arguments) {
		// protected URI createTemplateURI(String entry) {
		// return template0;
		// }
		// };
		// gen0.doGenerate(BasicMonitor.toMonitor(monitor));
		try {
			monitor.subTask("Loading...");
			URL resources = FileLocator.toFileURL(Platform
					.getBundle(org.muml.codegen.c.Activator.PLUGIN_ID).getEntry("resources"));
			File sourceFolder = new File(resources.toURI());
			Resource resource = new ResourceSetImpl().getResource(this.modelURI, true);
			int monitorCounter = 1;

			Resource modelResource = new ResourceSetImpl().getResource(modelURI, true);

			if (modelResource.getContents().get(0).eClass().getName() == "Diagram") {
				Diagram diagImpl = (Diagram) modelResource.getContents().get(0);

				ComponentInstanceConfiguration cic = (ComponentInstanceConfiguration) diagImpl.getElement();
				generateCIC(monitor, cic);

				/*
				 * monitor.subTask("Copying library to target folders...");
				 * 
				 * File target = new
				 * File(targetFolder.getLocationURI().toString().substring(5) +
				 * File.separator + cic.getName());
				 * this.copyFolder(sourceFolder, target);
				 * monitor.worked(++monitorCounter);
				 */

			} else if (modelResource.getContents().get(0).eClass().getName() == "RootNode") {
				RootNode rootNode = (RootNode) resource.getContents().get(0);

				for (ModelElementCategory mec : rootNode.getCategories()) {
					if (mec.getKey().matches("org.muml.pim.instance.category")) {

						for (ExtendableElement me : mec.getModelElements()) {
							ComponentInstanceConfiguration cic = (ComponentInstanceConfiguration) me;

							monitor.subTask("generating " + cic.getName() + "...");
							org.muml.codegen.c.main.Main gen0 = new org.muml.codegen.c.main.Main(
									cic, targetFolder.getLocation().toFile(), arguments);
							monitor.worked(++monitorCounter);

							monitor.subTask("Copying library to target folder...");
							File target = new File(targetFolder.getLocationURI().toString().substring(5)
									+ File.separator + cic.getName());
							FileUtils.copyDirectory(sourceFolder, target);
							monitor.worked(++monitorCounter);

							String generationID = org.eclipse.acceleo.engine.utils.AcceleoLaunchingUtil
									.computeUIProjectID("org.muml.codegen.c",
											"org.muml.codegen.c.main.Main", modelURI.toString(),
											targetFolder.getFullPath().toString(), new ArrayList<String>());
							gen0.setGenerationID(generationID);
							gen0.doGenerate(BasicMonitor.toMonitor(monitor));

						}
					}
				}
			}
		} catch (UnsupportedOperationException e) {
			e.printStackTrace();
		} catch (URISyntaxException e) {
			e.printStackTrace();
		}

	}

	public void generateCIC(IProgressMonitor monitor, ComponentInstanceConfiguration cic) throws IOException  {
		// System.out.println(cic.getName());

		monitor.subTask("generating " + cic.getName() + "...");
		org.muml.codegen.c.main.Main gen0 = new org.muml.codegen.c.main.Main(
				cic, targetFolder.getLocation().toFile(), arguments);
		String generationID = org.eclipse.acceleo.engine.utils.AcceleoLaunchingUtil.computeUIProjectID(
				"org.muml.codegen.c", "org.muml.codegen.c.main.Main",
				modelURI.toString(), targetFolder.getFullPath().toString(), new ArrayList<String>());
		gen0.setGenerationID(generationID);
		gen0.doGenerate(BasicMonitor.toMonitor(monitor));
		monitor.worked(1);
		URL resources = FileLocator.toFileURL(Platform
				.getBundle(org.muml.codegen.c.Activator.PLUGIN_ID).getEntry("resources"));
		File sourceFolder = new File(URLDecoder.decode(resources.getFile(), "UTF-8"));

		monitor.subTask("Copying library to target folder...");
		File target = new File(URLDecoder.decode(
				targetFolder.getLocationURI().toString().substring(5) + File.separator + cic.getName(), "UTF-8"));
		FileUtils.copyDirectory(sourceFolder, target);

		monitor.worked(1);
	}

	/**
	 * Finds the template in the plug-in. Returns the template plug-in URI.
	 * 
	 * @param bundleID
	 *            is the plug-in ID
	 * @param relativePath
	 *            is the relative path of the template in the plug-in
	 * @return the template URI
	 * @throws IOException
	 * @generated NOT
	 */
	@SuppressWarnings("unused")
	private URI getTemplateURI(String bundleID, IPath relativePath) throws IOException {
		Bundle bundle = Platform.getBundle(bundleID);
		if (bundle == null) {
			// no need to go any further
			return URI.createPlatformResourceURI(new Path(bundleID).append(relativePath).toString(), false);
		}
		URL url = bundle.getEntry(relativePath.toString());
		if (url == null && relativePath.segmentCount() > 1) {
			Enumeration<URL> entries = bundle.findEntries("/", "*.emtl", true);
			if (entries != null) {
				String[] segmentsRelativePath = relativePath.segments();
				while (url == null && entries.hasMoreElements()) {
					URL entry = entries.nextElement();
					IPath path = new Path(entry.getPath());
					if (path.segmentCount() > relativePath.segmentCount()) {
						path = path.removeFirstSegments(path.segmentCount() - relativePath.segmentCount());
					}
					String[] segmentsPath = path.segments();
					boolean equals = segmentsPath.length == segmentsRelativePath.length;
					for (int i = 0; equals && i < segmentsPath.length; i++) {
						equals = segmentsPath[i].equals(segmentsRelativePath[i]);
					}
					if (equals) {
						url = bundle.getEntry(entry.getPath());
					}
				}
			}
		}
		URI result;
		if (url != null) {
			result = URI.createPlatformPluginURI(new Path(bundleID).append(new Path(url.getPath())).toString(), false);
		} else {
			result = URI.createPlatformResourceURI(new Path(bundleID).append(relativePath).toString(), false);
		}
		return result;
	}

}
