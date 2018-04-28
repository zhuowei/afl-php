#include <php.h>
#include <Zend/zend_extensions.h>

static void aflphp_extension_fcall_begin_handler(zend_execute_data* frame) {
	printf("Fcall begin\n");
}

static int aflphp_user_opcode_handler(zend_execute_data* execute_data) {
	printf("opcode handler\n");
	return ZEND_USER_OPCODE_DISPATCH;
}

static int aflphp_extension_startup(zend_extension* extension) {
	return SUCCESS;
}

static void aflphp_extension_activate() {
	CG(compiler_options) |= ZEND_COMPILE_EXTENDED_INFO;
	static zend_uchar opcodes[] = {ZEND_JMPZ, ZEND_JMPNZ, ZEND_JMPZNZ,
		ZEND_JMPZ_EX, ZEND_JMPNZ_EX};
	for (unsigned int i = 0; i < sizeof(opcodes) / sizeof(*opcodes); i++) {
		zend_set_user_opcode_handler(opcodes[i], aflphp_user_opcode_handler);
	}
}

static void aflphp_extension_deactivate() {
	CG(compiler_options) &= ~ZEND_COMPILE_EXTENDED_INFO;
}

zend_extension_version_info extension_version_info = {
	ZEND_EXTENSION_API_NO,
	ZEND_EXTENSION_BUILD_ID
};

zend_extension zend_extension_entry = {
	.name = "aflphp",
	.version = "1.0.0",
	.author = "zhuowei",
	.URL = "http://zhuoweizhang.net",
	.copyright = "Copyright (c) 2018",

	.startup = aflphp_extension_startup,
	.shutdown = NULL,
	.activate = aflphp_extension_activate,
	.deactivate = aflphp_extension_deactivate,

	.message_handler = NULL,
	.op_array_handler = NULL,
	.statement_handler = NULL,
	.fcall_begin_handler = aflphp_extension_fcall_begin_handler,
	.fcall_end_handler = NULL,

	.op_array_ctor = NULL,
	.op_array_dtor = NULL,
	STANDARD_ZEND_EXTENSION_PROPERTIES
};
