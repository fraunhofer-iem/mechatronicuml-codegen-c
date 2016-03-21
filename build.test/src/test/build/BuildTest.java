package test.build;

import org.eclipse.core.internal.resources.WorkspaceRoot;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.IResourceVisitor;
import org.eclipse.core.resources.IWorkspace;
import org.eclipse.core.resources.IWorkspaceRoot;
import org.eclipse.core.resources.IncrementalProjectBuilder;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.NullProgressMonitor;
import org.junit.Test;

public class BuildTest {

	@Test
	public void test() throws CoreException {
		IProgressMonitor progressMonitor = new NullProgressMonitor();
		IWorkspace workspace = ResourcesPlugin.getWorkspace();
		IWorkspaceRoot root = ResourcesPlugin.getWorkspace().getRoot();
		root.accept(new IResourceVisitor() {

			@Override
			public boolean visit(IResource resource) throws CoreException {
				System.out.println(resource.getName());
				if(resource instanceof WorkspaceRoot)
				return true;
			return false;
			}
		});
		workspace.build(IncrementalProjectBuilder.FULL_BUILD, progressMonitor);
		workspace.save(true, progressMonitor);
	}

}
