package org.eclipse.acceleo.additions.beautifier;

import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.eclipse.cdt.core.dom.ast.IASTTranslationUnit;
import org.eclipse.cdt.core.dom.ast.gnu.cpp.GPPLanguage;
import org.eclipse.cdt.core.formatter.DefaultCodeFormatterConstants;
import org.eclipse.cdt.core.formatter.DefaultCodeFormatterOptions;
import org.eclipse.cdt.core.model.ILanguage;
import org.eclipse.cdt.core.parser.CodeReader;
import org.eclipse.cdt.core.parser.ParserUtil;
import org.eclipse.cdt.core.parser.ScannerInfo;
import org.eclipse.cdt.internal.formatter.CodeFormatterVisitor;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.jface.text.Document;
import org.eclipse.jface.text.IDocument;

@SuppressWarnings({ "deprecation", "restriction" })
public class CdtBeautifier {
	private final Log log = LogFactory.getLog(getClass());

	
	public String beautify(String source) {
		final DefaultCodeFormatterOptions settings = DefaultCodeFormatterOptions
				.getDefaultSettings();
		settings.line_separator = System.getProperty("line.separator");

		try {
			CodeFormatterVisitor codeFormatter = new CodeFormatterVisitor(
					settings, 0, source.length());
			IASTTranslationUnit ast = createTranslationUnit(settings.getMap(), source);
			IDocument document = new Document(source);
			codeFormatter.format(source, ast).apply(document);
			return document.get();
		} catch (Exception e) {
			log.error(e.getMessage());
			log.debug(e);
		}
		
		return source;
	}

	private IASTTranslationUnit createTranslationUnit(Map<?, ?> options, String source)
			throws CoreException {
		return getLanguage(options).getASTTranslationUnit(
				new CodeReader(source.toCharArray()), new ScannerInfo(), null,
				null, ParserUtil.getParserLogService());
	}

	/**
	 * Determines the language to be used based on the given options.
	 * 
	 * @param options
	 *            CDT formatter options
	 * @return a suitable ILanguage. GPPLanguage as default.
	 */
	private ILanguage getLanguage(Map<?, ?> options) {
		ILanguage language = (ILanguage) options
				.get(DefaultCodeFormatterConstants.FORMATTER_LANGUAGE);
		if (language == null) {
			language = GPPLanguage.getDefault();
		}
		return language;
	}


}
