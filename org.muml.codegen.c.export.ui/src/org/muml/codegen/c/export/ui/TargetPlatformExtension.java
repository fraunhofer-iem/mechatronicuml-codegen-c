package org.muml.codegen.c.export.ui;

import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IConfigurationElement;
import org.eclipse.core.runtime.Platform;

/**
 * Provides access to registered <code>org.muml.psm.allocation.algorithm.strategy</code>
 * extensions.
 *
 */
public class TargetPlatformExtension {
	private static final String extensionPointId =
			"org.muml.codegen.targetPlatformExtension";
	
	/**
	 * Returns descriptions for all registered
	 * <code>org.muml.psm.allocation.algorithm.strategy</code> extensions.
	 * 
	 * @return the allocationComputationStrategyDescrptions
	 */
	public static TargetPlatformDescription[] getDescriptions() {
		IConfigurationElement[] configurationElements = Platform
				.getExtensionRegistry()
				.getConfigurationElementsFor(extensionPointId);
		TargetPlatformDescription[] descriptions =
				new TargetPlatformDescription[configurationElements.length];
		for (int i = 0; i < configurationElements.length; i++) {
			descriptions[i] = new TargetPlatformDescription(
					configurationElements[i]);
		}
		return descriptions;
	}
	
	/**
	 * Encapsulates <code>org.muml.psm.allocation.algorithm.strategy</code>
	 * extension. It provides access to the strategy name and description.
	 * Additionally, the concrete <code>IAllocationComputationStrategy</code> can
	 * be created lazily.
	 *
	 */
	public static class TargetPlatformDescription {
		private static final String nameAttribute = "name";
		private static final String descriptionAttribute = "description";
		private static final String classAttribute = "class";
		private static final String invalidClass = "%s is no ITargetPlatformExtension";
		
		private IConfigurationElement configurationElement;
		
		public TargetPlatformDescription(
		IConfigurationElement configurationElement) {
			this.configurationElement = configurationElement;
		}
		
		
		public String getName() {
			return configurationElement.getAttribute(nameAttribute);
		}
		
		
		public String getDescription() {
			String description = configurationElement.getAttribute(
					descriptionAttribute);
			return description != null ? description : "";
		}
		
		/**
		 * Returns the <code>IAllocationComputationStrategy</code> object. A
		 * <code>IllegalStateException</code> is thrown, if the configuration
		 * element's <code>class</code> attribute does not correspond to
		 * an <code>IAllocationComputationStrategy</code>.
		 * 
		 * @return the allocation computation strategy
		 */
		
		public ITargetPlatformGenerator getTargetPlatform()
				throws CoreException {
			Object object = configurationElement.createExecutableExtension(
					classAttribute);
			if (!(object instanceof ITargetPlatformGenerator)) {
				throw new IllegalStateException(
						String.format(invalidClass, object));
			}
			return (ITargetPlatformGenerator) object;
		}
	}
}