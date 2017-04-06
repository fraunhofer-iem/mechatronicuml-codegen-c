package org.muml.codegen.c.export.ui;

import org.eclipse.core.resources.IContainer;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Status;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.jface.viewers.ArrayContentProvider;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.ISelectionChangedListener;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.viewers.LabelProvider;
import org.eclipse.jface.viewers.ListViewer;
import org.eclipse.jface.viewers.SelectionChangedEvent;
import org.eclipse.jface.viewers.StructuredSelection;
import org.eclipse.jface.wizard.WizardPage;
import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Label;
import org.eclipse.ui.IWorkbench;
import org.muml.codegen.c.export.ui.TargetPlatformExtension.TargetPlatformDescription;
import org.muml.core.export.operation.AbstractFujabaExportOperation;
import org.muml.core.export.operation.IFujabaExportOperation;
import org.muml.core.export.pages.AbstractFujabaExportSourcePage;
import org.muml.core.export.pages.AbstractFujabaExportTargetPage;
import org.muml.core.export.pages.ElementSelectionMode;
import org.muml.core.export.wizard.AbstractFujabaExportWizard;
import org.muml.pim.instance.ComponentInstanceConfiguration;

public class FujabaSourceCodeExportWizard extends AbstractFujabaExportWizard {

	private AbstractFujabaExportSourcePage sourcePage;
	private AbstractFujabaExportTargetPage targetPage;
	private TargetPlatformSelectionPage targetPlatformPage;

	@Override
	public void init(IWorkbench workbench, IStructuredSelection currentSelection) {
		super.init(workbench, currentSelection);
		setWindowTitle("Generate ANSI C99 Code");
		setDefaultPageImageDescriptor(Activator.imageDescriptorFromPlugin(Activator.PLUGIN_ID, "icons/GenC99.png"));
	}
	
	@Override
	public String wizardGetId() {
		return "de.uni_paderborn.fujaba.codegen.c.export";
	}

	public void addPages() {

		// Source page
		sourcePage = new AbstractFujabaExportSourcePage("source", toolkit, getResourceSet(), initialSelection) {


			
			@Override
			public String wizardPageGetSourceFileExtension() {
				return "muml";
			}

			@Override
			public boolean wizardPageSupportsSourceModelElement(EObject element) {
				return element instanceof ComponentInstanceConfiguration;
			}

			@Override
			public ElementSelectionMode wizardPageGetSupportedSelectionMode() {
				return ElementSelectionMode.ELEMENT_SELECTION_MODE_MULTI;
			}
			
		};
		addPage(sourcePage);

		// Target page
		targetPage = new AbstractFujabaExportTargetPage("target", toolkit) {

			@Override
			public boolean wizardPageSupportsOverwriteOption() {
				return false;
			}

			@Override
			public boolean wizardPageDirectoryDestination() {
				return true;
			}
			@Override
			public boolean wizardPageSupportsFilesystem() {
				return false;
			}
		};
		addPage(targetPage);
		
		targetPlatformPage = new TargetPlatformSelectionPage("target platform");
		addPage(targetPlatformPage);
	}

	@Override
	public IFujabaExportOperation wizardCreateExportOperation() {
		final EObject[] sourceElements = sourcePage.getSourceElements();
		final URI targetURI = targetPage.getDestinationURI();
		final IContainer target = (IContainer) ResourcesPlugin.getWorkspace().getRoot().findMember(targetURI.toPlatformString(true));

		final ITargetPlatformGenerator targetPlatform = targetPlatformPage.getTargetPlatform();
		
		return new AbstractFujabaExportOperation() {
			@Override
			protected IStatus doExecute(IProgressMonitor monitor) {
				try {
					
					for (EObject element : sourceElements){
						targetPlatform.generateSourceCode(element, target, monitor);
					}
				} catch (Exception e) {
					IStatus status = new Status(IStatus.ERROR, Activator.PLUGIN_ID, e.getMessage(), e);
					Activator.getDefault().getLog().log(status);
				} finally {
					try {
						target.getProject().refreshLocal(IResource.DEPTH_INFINITE, monitor);
					} catch (CoreException e) {
						e.printStackTrace();
					}
				}
								
							
					
				return Status.OK_STATUS;
			}
		};
	}
	
	
	public static class TargetPlatformSelectionPage extends WizardPage {
		private static final String title =
				"Select a targetPlatform";
		private static final String description =
				"The generated soruce code will be executable for the selected target platform.";
		private static final String invalidSelection =
				"Please select a target platform.";
		private ListViewer listViewer;
		private ITargetPlatformGenerator targetPlatformGenerator;

		public TargetPlatformSelectionPage(String pageName) {
			super(pageName);
			setTitle(title);
			setDescription(description);
			try {
				TargetPlatformDescription[] descriptions = TargetPlatformExtension.getDescriptions();
				targetPlatformGenerator = descriptions[0].getTargetPlatform();
			} catch (CoreException e) {
				e.printStackTrace();
			}
		}

		@Override
		public void createControl(Composite parent) {
			Composite composite = new Composite(parent, SWT.NONE);
			GridLayout layout = new GridLayout();
			layout.numColumns = 1;
			composite.setLayout(layout);
			setControl(composite);
			listViewer = new ListViewer(composite);
			listViewer.getControl().setLayoutData(
					new GridData(GridData.FILL_HORIZONTAL));
			listViewer.setContentProvider(new ArrayContentProvider());
			listViewer.setLabelProvider(new LabelProvider() {
				@Override
				public String getText(Object object) {
					if (object instanceof TargetPlatformDescription) {
						return ((TargetPlatformDescription) object).getName();
					}
					return "";
				}
			});
			final Label label = new Label(composite, SWT.LEFT);
			label.setLayoutData(new GridData(GridData.FILL_HORIZONTAL));
			ISelectionChangedListener strategyListener = new ISelectionChangedListener() {

				@Override
				public void selectionChanged(SelectionChangedEvent event) {
					if (event.getSelection() instanceof IStructuredSelection) {
						IStructuredSelection ssel = (IStructuredSelection) event.getSelection();
						if (ssel.getFirstElement() instanceof ITargetPlatformGenerator) {
							targetPlatformGenerator = (ITargetPlatformGenerator) ssel.getFirstElement();
							String text = targetPlatformGenerator
									.getDescription();
							label.setText(text);
						}
						validatePage();
					}
				}
				
			};
			listViewer.addSelectionChangedListener(strategyListener);
		}
		
		@Override
		public void setVisible(boolean visible) {
			super.setVisible(visible);
			if (visible) {
				TargetPlatformDescription[] descriptions = TargetPlatformExtension.getDescriptions();
				listViewer.setInput(descriptions);
				if (targetPlatformGenerator != null) {
					ISelection sel = new StructuredSelection(targetPlatformGenerator);
					listViewer.setSelection(sel, true);
				}
			}
		}
		
		protected void validatePage() {
			boolean isValid = targetPlatformGenerator != null;
			setPageComplete(isValid);
			if (!isValid) {
				setErrorMessage(invalidSelection);
			}
		}
		
		
		public ITargetPlatformGenerator getTargetPlatform() {
			return targetPlatformGenerator;
		}
		
	}


}
